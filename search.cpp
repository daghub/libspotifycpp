#include "search.h"
#include "artist.h"

NS_SPOTIFY_BEGIN

search::search(sp_session* session, const char* query, int track_offset, int track_count,
         int album_offset, int album_count, int artist_offset,
         int artist_count, int playlist_offset,
         int playlist_count, sp_search_type search_type)
{
  CHK_NULL(search_ = sp_search_create(session, query, track_offset, track_count,
                                      album_offset, album_count, artist_offset,
                                      artist_count, playlist_offset,
                                      playlist_count,  search_type, &cb_search_complete, this));

}

search::~search()
{
  sp_search_release(search_);
}

std::vector< artist_ptr > search::artists()
{
  std::vector< artist_ptr > ret;
  int n = sp_search_num_artists(search_);
  for (int i = 0; i < n; ++i) {
    ret.push_back(artist_ptr(new artist(sp_search_artist(search_, i))));
  }
  return ret;
}

void search::search_complete()
{
  complete();
}

void SP_CALLCONV search::cb_search_complete(sp_search*, void *userdata)
{
  reinterpret_cast< search* >(userdata)->search_complete();
}

NS_SPOTIFY_END

