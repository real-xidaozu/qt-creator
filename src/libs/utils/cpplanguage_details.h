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

#pragma once

#include <QFlags>

namespace Utils {

enum class Language : unsigned char { C, Cxx };

enum class LanguageVersion : unsigned char {
    C89,
    C99,
    C11,
    C18,
    LatestC = C18,
    CXX98 = 32,
    CXX03,
    CXX11,
    CXX14,
    CXX17,
    CXX2a,
    LatestCxx = CXX2a,
};

enum class LanguageExtension : unsigned char {
    None = 0,

    Gnu = 1 << 0,
    Microsoft = 1 << 1,
    Borland = 1 << 2,
    OpenMP = 1 << 3,
    ObjectiveC = 1 << 4,

    All = Gnu | Microsoft | Borland | OpenMP | ObjectiveC
};

Q_DECLARE_FLAGS(LanguageExtensions, LanguageExtension)

constexpr LanguageExtension operator|(LanguageExtension first, LanguageExtension second)
{
    return static_cast<LanguageExtension>(
        (static_cast<unsigned char>(first) | static_cast<unsigned char>(second)));
}

constexpr bool operator&&(LanguageExtension first, LanguageExtension second)
{
    return static_cast<unsigned char>(first) & static_cast<unsigned char>(second);
}

} // namespace Utils
