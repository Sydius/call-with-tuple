/*
Copyright 2011 Christopher Allen Ogden. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY CHRISTOPHER ALLEN OGDEN ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER ALLEN OGDEN OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Christopher Allen Ogden.
*/

#pragma once
#include <tuple>

template <typename Ret, unsigned int N>
struct CallWithTuple
{
    template <typename Callable, typename... ArgsTuple, typename... Args>
    static Ret callWithTuple(Callable && callable, const std::tuple<ArgsTuple...> & tuple, Args && ... args)
    {
        return CallWithTuple<Ret, N-1>::callWithTuple(std::forward<Callable>(callable), tuple,
                std::get<N-1>(tuple), std::forward<Args>(args)...);
    }
};

template <typename Ret>
struct CallWithTuple<Ret, 0>
{
    template <typename Callable, typename... ArgsTuple, typename... Args>
    static Ret callWithTuple(Callable && callable, const std::tuple<ArgsTuple...> & tuple, Args && ... args)
    {
        return callable(std::forward<Args>(args)...);
    }
};

/**
 * Call a function pointer or callable object using a tuple for the arguments.
 *
 * @param callable  A function pointer or callable object.
 * @param tuple     Tuple containing arguments to be passed.
 * @param extra...  Extra arguments to pass to the function
 * @return          Return value passed back from the call.
 */
template <typename Ret, typename Callable, typename... ArgsTuple, typename... Extra>
Ret callWithTuple(Callable && callable, const std::tuple<ArgsTuple...> & tuple, Extra && ... extra)
{
    return CallWithTuple<Ret, sizeof...(ArgsTuple)>::callWithTuple(std::forward<Callable>(callable), tuple, std::forward<Extra>(extra)...);
}
