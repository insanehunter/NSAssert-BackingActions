NSAssert+BackingActions
=======================

Assertion macros to make your program more robust even in Release builds.

If you are a battle hardened game development veteran or just a fan of assertions, you know that these checks are not included in Release builds when `NS_BLOCK_ASSERTIONS` macro is defined.

But what would happen to your application if it encounters a rare untested case where assertion fails in Release? It will continue execution and do some senseless job, or even crash!

So here's where `NSAssert+BackingActions` shines! You can supply a backing action, that works only in Release to redirect program flow and avoid executing code with failed precondition.

## Usage
Add `NSAssert+BackingActions.h` to your precompiled header. And now you can use the following macros:

* `NSAssertOrReturn`, `NSParameterAssertOrReturn` - does `return` in Release if assertion condition fails.
* `NSAssertOrReturnNil`, `NSParameterOrReturnNil` - all the same, but returns nil.
* `NSAssertOrReturnNO`, `NSParameterAssertOrReturnNO`
* `NSAssertOrBreak`, `NSParameterAssertOrBreak`
* `NSAssertOrContinue`, `NSParameterAssertOrContinue`

By default when action backed assertion fails in Release, it prints warning using `NSLog`. You can suppress logging by defining `NS_ASSERT_SUPRESS_BACKING_ACTION_LOGGING` macro or provide your own logging facility by defining `NSReleaseAssertionLog(args, …)` macro.

## Example
    - (NSArray *) documentsFromDate:(NSDate *)startDate toDate:(NSDate *)endDate
    {
        NSParameterAssertOrReturnNil(startDate != nil);
        NSParameterAssertOrReturnNil(endDate != nil);
        
        ...
    }
    
If somewhere in your code you call `documentsFromDate:toDate` with `nil`, it will raise exception in Debug or return `nil` in Release. 

## Requirements
I presume `NSAssert+BackingActions` should work in Xcode 4.0+ both on OSX and iOS, in both ARC and non-ARC environments.

## License
This code is distributed under the terms and conditions of the MIT license.

Copyright (c) 2012 Sergei Cherepanov.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.