#include "refresher.h"

Refresher::Refresher(Refreshable *refreshable)
{
    m_refreshable = refreshable;
}

Refresher::~Refresher()
{
    if (m_refreshable != nullptr)
        m_refreshable->refresh();
}
