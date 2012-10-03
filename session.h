#ifndef SESSION_H
#define SESSION_H

#include <libspotify/api.h>
#include <boost/exception/all.hpp>
#include <boost/utility.hpp>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>

namespace spotify {

struct error : virtual boost::exception , virtual std::exception {};
typedef boost::error_info< struct tag_sp_error, sp_error > sp_error_info;
typedef boost::error_info< struct tag_call, std::string > sp_call_info;

#define CHK(x) \
  { sp_error res = x; if (res != SP_ERROR_OK) BOOST_THROW_EXCEPTION(error() << sp_error_info(res) << sp_call_info(#x)); }
#define CHK_NULL(x) \
  { if (!(x)) BOOST_THROW_EXCEPTION(error() << sp_call_info(#x)); }

namespace sig = boost::signals2;

class search;
class session : boost::noncopyable
{
public:
  session();
  virtual ~session();

  void login(const char* username, const char* password, bool remember_me, const char* blob) const;
  boost::shared_ptr< search > create_search(const char* query, int track_offset, int track_count,
                                            int album_offset, int album_count, int artist_offset,
                                            int artist_count, int playlist_offset,
                                            int playlist_count, sp_search_type search_type);

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


