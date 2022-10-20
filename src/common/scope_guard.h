#pragma once

#include <functional>


class scope_guard
{
public:
    explicit scope_guard(std::function<void()> on_exit_scope)
        : exit_scope(on_exit_scope), dismissed(false) {}
    ~scope_guard() { if (!dismissed) {exit_scope();} }
    void dismiss() const throw()
    { dismissed = true; }   // support rollback mode

private:
    std::function<void()> exit_scope;
    mutable bool dismissed;

private:
    scope_guard(scope_guard const&);
    scope_guard& operator=(scope_guard const&);
};


#define SCOPEGUARD_LINENAME_CAT(name, line)  name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) scope_guard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)


/* 
example 1 :
Acquire Resource
ON_SCOPE_EXIT([&]{ Release Resource }
.......................................
example 2 :
scope_guard on_failure_rollback([&]{ rollback });
// do something that could fail
on_failure_rollback.dismiss();
*/


/*
* Copyright (c) 1992-2016 by Aaron Wang.  ALL RIGHTS RESERVED.
* Consult your license regarding permissions and restrictions.
*/
