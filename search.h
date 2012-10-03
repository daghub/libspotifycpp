#ifndef SEARCH_H
#define SEARCH_H

#include <boost/utility.hpp>
#include <boost/signals2.hpp>
#include <vector>
#include "session.h"

class sp_search;

namespace spotify {

namespace sig = boost::signals2;

class search : boost::noncopyable
{
public:
  ~search();

  std::vector< artist_ptr > artists();
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
}

#endif
