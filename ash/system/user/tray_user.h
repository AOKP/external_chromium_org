// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_USER_TRAY_USER_H_
#define ASH_SYSTEM_USER_TRAY_USER_H_

#include "ash/ash_export.h"
#include "ash/session_state_delegate.h"
#include "ash/system/tray/system_tray_item.h"
#include "ash/system/user/user_observer.h"
#include "base/compiler_specific.h"

namespace gfx {
class Rect;
}

namespace views {
class ImageView;
class Label;
}

namespace ash {
namespace internal {

namespace tray {
class UserView;
class RoundedImageView;
}

class ASH_EXPORT TrayUser : public SystemTrayItem,
                            public UserObserver {
 public:
  // The given |multiprofile_index| is the number of the user in a multi profile
  // scenario. Index #0 is the running user, the other indices are other
  // logged in users (if there are any). Only index #0 will add an icon to
  // the system tray.
  TrayUser(SystemTray* system_tray, MultiProfileIndex index);
  virtual ~TrayUser();

  // Allows unit tests to see if the item was created.
  enum TestState {
    HIDDEN,               // The item is hidden.
    SEPARATOR,            // the item gets shown as a separator.
    SHOWN,                // The item gets presented to the user.
    HOVERED,              // The item is hovered and presented to the user.
    ACTIVE,               // The item was clicked and can add a user.
    ACTIVE_BUT_DISABLED   // The item was clicked anc cannot add a user.
  };
  TestState GetStateForTest() const;

  // Returns the bounds of the user panel in screen coordinates.
  // Note: This only works when the panel shown.
  gfx::Rect GetUserPanelBoundsInScreenForTest() const;

 private:
  // Overridden from SystemTrayItem.
  virtual views::View* CreateTrayView(user::LoginStatus status) OVERRIDE;
  virtual views::View* CreateDefaultView(user::LoginStatus status) OVERRIDE;
  virtual views::View* CreateDetailedView(user::LoginStatus status) OVERRIDE;
  virtual void DestroyTrayView() OVERRIDE;
  virtual void DestroyDefaultView() OVERRIDE;
  virtual void DestroyDetailedView() OVERRIDE;
  virtual void UpdateAfterLoginStatusChange(user::LoginStatus status) OVERRIDE;
  virtual void UpdateAfterShelfAlignmentChange(
      ShelfAlignment alignment) OVERRIDE;

  // Overridden from UserObserver.
  virtual void OnUserUpdate() OVERRIDE;

  void UpdateAvatarImage(user::LoginStatus status);

  // The user index to use.
  MultiProfileIndex multiprofile_index_;

  tray::UserView* user_;

  // View that contains label and/or avatar.
  views::View* layout_view_;
  tray::RoundedImageView* avatar_;
  views::Label* label_;

  // True if this element is the separator and it is shown.
  bool separator_shown_;

  DISALLOW_COPY_AND_ASSIGN(TrayUser);
};

}  // namespace internal
}  // namespace ash

#endif  // ASH_SYSTEM_USER_TRAY_USER_H_
