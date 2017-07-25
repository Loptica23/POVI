#pragma once

class Refreshable
{
public:
    Refreshable();
    virtual ~Refreshable();

    virtual void refresh() = 0;
};
