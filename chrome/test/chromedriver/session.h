// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_CHROMEDRIVER_SESSION_H_
#define CHROME_TEST_CHROMEDRIVER_SESSION_H_

#include <list>
#include <string>

#include "base/basictypes.h"
#include "base/files/scoped_temp_dir.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "chrome/test/chromedriver/basic_types.h"
#include "chrome/test/chromedriver/chrome/geoposition.h"

namespace base {
class DictionaryValue;
}

class Chrome;
class Status;
class WebDriverLog;
class WebView;

struct FrameInfo {
  FrameInfo(const std::string& parent_frame_id,
            const std::string& frame_id,
            const std::string& chromedriver_frame_id);

  std::string parent_frame_id;
  std::string frame_id;
  std::string chromedriver_frame_id;
};

struct Session {
  static const int kDefaultPageLoadTimeoutMs;

  explicit Session(const std::string& id);
  Session(const std::string& id, scoped_ptr<Chrome> chrome);
  ~Session();

  Status GetTargetWindow(WebView** web_view);

  void SwitchToTopFrame();
  void SwitchToSubFrame(const std::string& frame_id,
                        const std::string& chromedriver_frame_id);
  std::string GetCurrentFrameId() const;

  const std::string id;
  bool quit;
  bool detach;
  scoped_ptr<Chrome> chrome;
  std::string window;
  int sticky_modifiers;
  // List of |FrameInfo|s for each frame to the current target frame from the
  // first frame element in the root document. If target frame is window.top,
  // this list will be empty.
  std::list<FrameInfo> frames;
  WebPoint mouse_position;
  int implicit_wait;
  int page_load_timeout;
  int script_timeout;
  scoped_ptr<std::string> prompt_text;
  scoped_ptr<Geoposition> overridden_geoposition;
  // Logs that populate from DevTools events.
  ScopedVector<WebDriverLog> devtools_logs;
  base::ScopedTempDir temp_dir;
  const scoped_ptr<base::DictionaryValue> capabilities;

 private:
  scoped_ptr<base::DictionaryValue> CreateCapabilities();
};

#endif  // CHROME_TEST_CHROMEDRIVER_SESSION_H_
