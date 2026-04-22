#pragma once

#include "ITagProvider.h"

class ITagUI;

class TagProviderPreset : public ITagProvider
{
public:
    explicit TagProviderPreset(ITagUI& tagUI);
    std::vector<RFIDTag> GetTags() override;

private:
    ITagUI& m_tagUI;
};