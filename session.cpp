#include <memory.h>
#include "session.h"
#include "search.h"
#include "playlistcontainer.h"
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
  callbacks_.log_message = &cb_log_message;

  CHK(sp_session_create(&config_, &session_));
  g_session_ = this;
}

session::~session()
{
  sp_session_release(session_);
  g_session_ = 0;
}

void session::login(const char* username, const char* password, bool remember_me, const char* blob) const
{
  CHK(sp_session_login(session_, username, password, remember_me, blob));
}

playlistcontainer_ptr session::playlistcontainer() const
{
  return playlistcontainer_ptr(new spotify::playlistcontainer(
      sp_session_playlistcontainer(session_))
                               );
}

boost::shared_ptr< search > session::search(const char* query, int track_offset, int track_count,
                                                   int album_offset, int album_count, int artist_offset,
                                                   int artist_count, int playlist_offset,
                                                   int playlist_count, sp_search_type search_type)
{
  return search_ptr(new spotify::search(session_, query, track_offset, track_count,
                                                 album_offset, album_count, artist_offset,
                                                 artist_count, playlist_offset,
                                                 playlist_count,  search_type));
}

int session::process_events()
{
  int next_timeout = 0;
  CHK(sp_session_process_events(session_, &next_timeout));
  return next_timeout;
}

void SP_CALLCONV session::cb_logged_in(sp_session*, sp_error err)
{
  g_session_->logged_in(err);
}

void SP_CALLCONV session::cb_notify_main_thread(sp_session*)
{
  if (g_session_)
    g_session_->notify_main_thread();
}

void SP_CALLCONV session::cb_log_message(sp_session*, const char* data)
{
  if (g_session_)
    g_session_->log_message(data);
}

}

