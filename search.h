#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "base.h"

class sp_search;

NS_SPOTIFY_BEGIN

class search : boost::noncopyable
{
public:
  ~search();

  std::vector< artist_ptr > artists() const;
  size_t total_artists() const;

  sp_error error() const;
  bool is_loaded() const;

  sig::signal< void(void) > complete;

private:
  search(sp_session* session, const char* query, int track_offset, int track_count,
         int album_offset, int album_count, int artist_offset,
         int artist_count, int playlist_offset,
         int playlist_count, sp_search_type search_type);

  void search_complete();
  static void SP_CALLCONV cb_search_complete(sp_search* result, void *userdata);

  friend class session;

  sp_search* search_;
};

NS_SPOTIFY_END

#endif
