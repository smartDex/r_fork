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

#ifndef cbc_PEERFINDER_REPORTING_H_INCLUDED
#define cbc_PEERFINDER_REPORTING_H_INCLUDED

namespace cbc {
namespace PeerFinder {

/** Severity levels for test reporting.
    This allows more fine grained control over reporting for diagnostics.
*/
struct Reporting
{
    // Report simulation parameters
    static bool const params = true;

    // Report simulation crawl time-evolution
    static bool const crawl = true;

    // Report nodes aggregate statistics
    static bool const nodes = true;

    // Report nodes detailed information
    static bool const dump_nodes = false;
};

}
}

#endif
