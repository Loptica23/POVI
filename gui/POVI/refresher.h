#pragma once
#include "refreshable.h"

class Refresher
{
public:
    Refresher(Refreshable* refreshable);
    virtual ~Refresher();

private:
    Refreshable* m_refreshable;
};
