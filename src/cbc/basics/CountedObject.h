//------------------------------------------------------------------------------
/*
    This file is part of cbcd: https://github.com/cbc/cbcd
    Copyright (c) 2012, 2013 cbc Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef cbc_BASICS_COUNTEDOBJECT_H_INCLUDED
#define cbc_BASICS_COUNTEDOBJECT_H_INCLUDED

#include <atomic>
#include <string>
#include <utility>
#include <vector>

namespace cbc {

/** Manages all counted object types. */
class CountedObjects
{
public:
    static CountedObjects& getInstance ();

    using Entry = std::pair <std::string, int>;
    using List = std::vector <Entry>;

    List getCounts (int minimumThreshold) const;

public:
    /** Implementation for @ref CountedObject.

        @internal
    */
    class CounterBase
    {
    public:
        CounterBase ();

        virtual ~CounterBase ();

        int increment () noexcept
        {
            return ++m_count;
        }

        int decrement () noexcept
        {
            return --m_count;
        }

        int getCount () const noexcept
        {
            return m_count.load ();
        }

        CounterBase* getNext () const noexcept
        {
            return m_next;
        }

        virtual char const* getName () const = 0;

    private:
        virtual void checkPureVirtual () const = 0;

    protected:
        std::atomic <int> m_count;
        CounterBase* m_next;
    };

private:
    CountedObjects ();
    ~CountedObjects ();

private:
    std::atomic <int> m_count;
    std::atomic <CounterBase*> m_head;
};

//------------------------------------------------------------------------------

/** Tracks the number of instances of an object.

    Derived classes have their instances counted automatically. This is used
    for reporting purposes.

    @ingroup cbc_basics
*/
template <class Object>
class CountedObject
{
public:
    CountedObject ()
    {
        getCounter ().increment ();
    }

    CountedObject (CountedObject const&)
    {
        getCounter ().increment ();
    }

    CountedObject& operator=(CountedObject const&) = default;

    ~CountedObject ()
    {
        getCounter ().decrement ();
    }

private:
    class Counter : public CountedObjects::CounterBase
    {
    public:
        Counter () { }

        char const* getName () const
        {
            return Object::getCountedObjectName ();
        }

        void checkPureVirtual () const { }
    };

private:
    static Counter& getCounter()
    {
        static Counter c;
        return c;
    }
};

} // cbc

#endif
