/******************************************************************************
 * Copyright (c) 2000-2018 Ericsson Telecom AB
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 *
 * Contributors:
 *   Balasko, Jeno
 *   Raduly, Csaba
 *
 ******************************************************************************/
#include "LoggerPlugin.hh"
#include "ILoggerPlugin.hh"

#include <assert.h>
#include <dlfcn.h>

void LoggerPlugin::load()
{
  if (this->filename_) {
    // Dynamic plug-in requires dynamic runtime. Panic.
    TTCN_Logger::fatal_error("Static runtime cannot load plugins");
  } else {
    // Static plug-in. We simply instantiate the class without any `dl*()'.
    assert(this->create_);
    this->ref_ = this->create_();
  }

  this->ref_->init();
  this->is_log2str_capable_ = this->ref_->is_log2str_capable();
}

// Completely destroy the logger plug-in and make it useless.  However,
// reloading is possible.  This should be called before the logger is
// deleted.
void LoggerPlugin::unload()
{
  if (!this->ref_) return;
  this->ref_->fini();
  if (this->filename_) {
    // This cannot happen.
    TTCN_Logger::fatal_error("Static runtime cannot have plugins");
  } else {
    // For static plug-ins, it's simple.
    delete this->ref_;
    this->create_ = NULL;
  }
  this->ref_ = NULL;
}
