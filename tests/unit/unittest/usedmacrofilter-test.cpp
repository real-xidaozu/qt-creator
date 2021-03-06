/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "googletest.h"

#include <usedmacrofilter.h>

namespace  {

using ClangBackEnd::FilePathId;
using ClangBackEnd::SourceEntries;
using ClangBackEnd::SourceEntry;
using ClangBackEnd::SourceType;
using ClangBackEnd::UsedMacro;
using ClangBackEnd::UsedMacros;
using ClangBackEnd::CompilerMacro;
using ClangBackEnd::CompilerMacros;

class UsedMacroFilter : public testing::Test
{
protected:
    SourceEntries includes{{1, SourceType::UserInclude, 0},
                           {2, SourceType::SystemInclude, 0},
                           {3, SourceType::ProjectInclude, 0},
                           {4, SourceType::TopSystemInclude, 0},
                           {5, SourceType::TopProjectInclude, 0}};
    UsedMacros usedMacros{{"YI", 1}, {"ER", 2}, {"SAN", 3}, {"SE", 4}, {"WU", 5}};
    CompilerMacros compileMacros{{"YI", "1", 1},
                                 {"ER", "2", 2},
                                 {"SAN", "3", 3},
                                 {"SE", "4", 4},
                                 {"WU", "5", 5},
                                 {"LIANG", "2", 6}};
};

TEST_F(UsedMacroFilter, SystemIncludes)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    ASSERT_THAT(filter.systemIncludes, ElementsAre(FilePathId{2}, FilePathId{4}));
}

TEST_F(UsedMacroFilter, ProjectIncludes)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    ASSERT_THAT(filter.projectIncludes, ElementsAre(FilePathId{3}, FilePathId{5}));
}

TEST_F(UsedMacroFilter, TopSystemIncludes)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    ASSERT_THAT(filter.topSystemIncludes, ElementsAre(FilePathId{4}));
}

TEST_F(UsedMacroFilter, TopProjectIncludes)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    ASSERT_THAT(filter.topProjectIncludes, ElementsAre(FilePathId{5}));
}


TEST_F(UsedMacroFilter, AllIncludes)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    ASSERT_THAT(filter.allIncludes,
                ElementsAre(FilePathId{1}, FilePathId{2}, FilePathId{3}, FilePathId{4}, FilePathId{5}));
}

TEST_F(UsedMacroFilter, SystemUsedMacros)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    ASSERT_THAT(filter.systemUsedMacros, ElementsAre(UsedMacro{"ER", 2}, UsedMacro{"SE", 4}));
}

TEST_F(UsedMacroFilter, ProjectUsedMacros)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    ASSERT_THAT(filter.projectUsedMacros, ElementsAre(UsedMacro{"WU", 5}, UsedMacro{"SAN", 3}));
}

TEST_F(UsedMacroFilter, SystemCompileMacros)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    filter.filter(compileMacros);

    ASSERT_THAT(filter.systemCompilerMacros,
                ElementsAre(CompilerMacro{"ER", "2", 2}, CompilerMacro{"SE", "4", 4}));
}

TEST_F(UsedMacroFilter, ProjectCompileMacros)
{
    ClangBackEnd::UsedMacroFilter filter(includes, usedMacros);

    filter.filter(compileMacros);

    ASSERT_THAT(filter.projectCompilerMacros,
                ElementsAre(CompilerMacro{"WU", "5", 5}, CompilerMacro{"SAN", "3", 3}));
}

} // namespace
