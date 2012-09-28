#include <memory.h>
#include "session.h"
#include "appkey.h"

namespace spotify {

session* g_session_ = 0;

session::session()
{
  memset(&config_, 0, sizeof(config_));
  config_.user_agent = "libspotifycpp"; //
  config_.api_version = SPOTIFY_API_VERSION;
  config_.cache_location = "tmp"; //
  config_.settings_location = "tmp"; //
  config_.application_key = g_appkey;
  config_.application_key_size = g_appkey_size;

  memset(&callbacks_, 0, sizeof(callbacks_));
  config_.callbacks = &callbacks_;
  callbacks_.notify_main_thread = &cb_notify_main_thread;
  callbacks_.logged_in = &cb_logged_in;

  CHK(sp_session_create(&config_, &session_));
  g_session_ = this;
}

session::~session()
{
  g_session_ = 0;
}

void session::login(const char* username, const char* password, bool remember_me, const char* blob) const
{
  CHK(sp_session_login(session_, username, password, remember_me, blob));
}

int session::process_events()
{
  int next_timeout = 0;
  CHK(sp_session_process_events(session_, &next_timeout));
  return next_timeout;
}

void session::notify_main_thread()
{
  // Implemented by the user
}

void SP_CALLCONV session::cb_logged_in(sp_session* session, sp_error err)
{
  g_session_->logged_in(err);
}

void SP_CALLCONV session::cb_notify_main_thread(sp_session* session)
{
  if (g_session_)
    g_session_->notify_main_thread();
}

}

