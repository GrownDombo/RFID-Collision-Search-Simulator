#include <iostream>

#include <string>

#include "ITagUI.h"
#include "ITagProvider.h"
#include "TagUIConsole.h"
#include "TagProvider_Factory.h"
#include "TagSearcherRecursive.h"
#include "TagSearcherIterative.h"
#include "ITagSearcher.h"
#include "RFIDTag.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace
{
    void ConfigureConsoleEncoding()
    {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
    }

    void WaitForExit()
    {
        std::cout << std::endl << "종료하려면 Enter 키를 누르세요...";

        std::string ignored;
        std::getline(std::cin, ignored);
    }
}

int main()
{
    ConfigureConsoleEncoding();

    TagUIConsole ui;
    TagProvider_Factory factory(ui);

    const int menu = ui.ReadMenu();

    std::unique_ptr<ITagProvider> tagProvider = factory.Create(menu);
    if (tagProvider == nullptr)
    {
        ui.ShowError("TAG Provider 생성에 실패했습니다.");
        WaitForExit();
        return 1;
    }

    const std::vector<RFIDTag> tags = tagProvider->GetTags();
    ui.ShowTags(tags);

    std::unique_ptr<ITagSearcher> recursiveSearcher = std::make_unique<TagSearcherRecursive>();
    std::unique_ptr<ITagSearcher> iterativeSearcher = std::make_unique<TagSearcherIterative>();

    const SearchResult recursiveResult = recursiveSearcher->Search(tags);
    const SearchResult iterativeResult = iterativeSearcher->Search(tags);

    ui.ShowSearchResult(recursiveSearcher->GetName(), recursiveResult);
    ui.ShowSearchResult(iterativeSearcher->GetName(), iterativeResult);
    ui.ShowComparison(recursiveSearcher->GetName(), recursiveResult, iterativeSearcher->GetName(), iterativeResult);

    WaitForExit();
    return 0;
}
