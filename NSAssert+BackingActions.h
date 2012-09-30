/*
 * NSAssert+BackingActions.h
 *
 * This header provides NSAssert based macros which provide some backing actions
 * to be performed when NS_BLOCK_ASSERTIONS is defined.
 *
 * Possible actions:
 *
 *      return
 *      return nil
 *      break
 *      continue
 *
 * Unless the NS_ASSERT_SUPRESS_BACKING_ACTION_LOGGING is defined, all assertions
 * that failed in Release mode are logged.
 *
 * (c) Sergei Cherepanov, 2012
 */
#ifndef _NSAssert_BackingActions_H_
#define _NSAssert_BackingActions_H_
#import <Foundation/NSException.h>

#if !defined(NS_BLOCK_ASSERTIONS)
    #define NSAssertOrReturn    NSAssert
    #define NSAssertOrReturnNil NSAssert
    #define NSAssertOrReturnNO  NSAssert
    #define NSAssertOrBreak     NSAssert
    #define NSAssertOrContinue  NSAssert
    
    #define NSParameterAssertOrReturn    NSParameterAssert
    #define NSParameterAssertOrReturnNil NSParameterAssert
    #define NSParameterAssertOrReturnNO  NSParameterAssert
    #define NSParameterAssertOrBreak     NSParameterAssert
    #define NSParameterAssertOrContinue  NSParameterAssert
#else // !defined(NS_BLOCK_ASSERTIONS)

    #if !defined(NSReleaseAssertionLog)
        #if !defined(NS_ASSERT_SUPRESS_BACKING_ACTION_LOGGING)
            #define NSReleaseAssertionLog(desc, ...)    NSLog(desc, __VA_ARGS__)
        #else
            #define NSReleaseAssertionLog(desc, ...)
        #endif // !defined(NS_ASSERT_SUPRESS_BACKING_ACTION_LOGGING)
    #endif // !defined(NSReleaseAssertionLog)

    #define NSAssertWithReleaseAction(releaseAction, condition, desc, ...)                  \
        {                                                                                   \
            if (!(condition)) {                                                             \
                NSReleaseAssertionLog(@"*** Assertion failure in %@, %s:%d. Reason: %@",    \
                    NSStringFromSelector(_cmd), __FILE__, __LINE__,                         \
                    [NSString stringWithFormat:desc, __VA_ARGS__]);                         \
                releaseAction;                                                              \
            }                                                                               \
        }
    
    #define NSAssertOrReturn(condition, desc, ...) \
                    NSAssertWithReleaseAction(return, condition, desc, __VA_ARGS__)
    #define NSAssertOrReturnNil(condition, desc, ...) \
                    NSAssertWithReleaseAction(return nil, condition, desc, __VA_ARGS__)
    #define NSAssertOrReturnNO(condition, desc, ...) \
                    NSAssertWithReleaseAction(return NO, condition, desc, __VA_ARGS__)
    #define NSAssertOrBreak(condition, desc, ...) \
                    NSAssertWithReleaseAction(break, condition, desc, __VA_ARGS__)
    #define NSAssertOrContinue(condition, desc, ...) \
                    NSAssertWithReleaseAction(continue, condition, desc, __VA_ARGS__)
    
    #define NSParameterAssertOrReturn(condition) \
                    NSAssertWithReleaseAction(return, condition, @"Invalid parameter not satisfying: %s", #condition)
    #define NSParameterAssertOrReturnNil(condition) \
                    NSAssertWithReleaseAction(return nil, condition, @"Invalid parameter not satisfying: %s", #condition)
    #define NSParameterAssertOrReturnNO(condition) \
                    NSAssertWithReleaseAction(return NO, condition, @"Invalid parameter not satisfying: %s", #condition)
    #define NSParameterAssertOrBreak(condition) \
                    NSAssertWithReleaseAction(break, condition, @"Invalid parameter not satisfying: %s", #condition)
    #define NSParameterAssertOrContinue(condition) \
                    NSAssertWithReleaseAction(continue, condition, @"Invalid parameter not satisfying: %s", #condition)

#endif // !defined(NS_BLOCK_ASSERTIONS)

#endif // _NSAssert_BackingActions_H_
