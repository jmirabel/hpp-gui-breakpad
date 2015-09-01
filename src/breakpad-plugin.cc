// Copyright (c) 2015, Joseph Mirabel
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-gui-breakpad.
// hpp-gui-breakpad is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-gui-breakpad is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-gui-breakpad. If not, see <http://www.gnu.org/licenses/>.

#include "hpp/gui/plugin/breakpad-plugin.hh"
#include <QDebug>

BreakPadPlugin::BreakPadPlugin () :
  eh (NULL)
{}

BreakPadPlugin::~BreakPadPlugin ()
{
  if (eh != NULL)
    delete eh;
}

bool BreakPadPlugin::dumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                         void* context,
                         bool succeeded)
{
  qDebug() << "Dump path:" << descriptor.path();
  return succeeded;
}

void BreakPadPlugin::init ()
{
  eh = new google_breakpad::ExceptionHandler (
      google_breakpad::MinidumpDescriptor ("/tmp"),
      NULL, BreakPadPlugin::dumpCallback, NULL, true, -1);
}

QString BreakPadPlugin::name () const
{
  return QString ("BreakPad plugin");
}

Q_EXPORT_PLUGIN2 (breakpadplugin, BreakPadPlugin)
