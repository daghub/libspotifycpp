#ifndef SESSION_H
#define SESSION_H

#include "base.h"

namespace spotify {


class session : boost::noncopyable
{
public:
  session();
  virtual ~session();

  void login(const char* username, const char* password, bool remember_me, const char* blob) const;
  playlistcontainer_ptr playlistcontainer() const;
  search_ptr search(const char* query, int track_offset, int track_count,
                                            int album_offset, int album_count, int artist_offset,
                                            int artist_count, int playlist_offset,
                                            int playlist_count, sp_search_type search_type);

  std::string remembered_user() const;
  int process_events();

  virtual void notify_main_thread() {}
  virtual void log_message(const char*) const {}

  sig::signal< void(sp_error) > logged_in;

private:

  static void SP_CALLCONV cb_logged_in(sp_session* session, sp_error err);
  static void SP_CALLCONV cb_notify_main_thread(sp_session* session);
  static void SP_CALLCONV cb_log_message(sp_session* session, const char* data);

  sp_session_config config_;
  sp_session_callbacks callbacks_;
  sp_session* session_;
};

}

#endif // SESSION_H


