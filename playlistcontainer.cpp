#include "playlistcontainer.h"
#include "playlist.h"

NS_SPOTIFY_BEGIN

sp_playlistcontainer_callbacks playlistcontainer::cb_;


playlistcontainer::playlistcontainer(sp_playlistcontainer* pc) : pc_(pc)
{
  sp_playlistcontainer_add_ref(pc_);
  cb_.playlist_added = &cb_playlist_added;
  cb_.playlist_removed = &cb_playlist_removed;
  cb_.playlist_moved = &cb_playlist_moved;
  cb_.container_loaded = &cb_container_loaded;
  sp_playlistcontainer_add_callbacks(pc_, &cb_, this);
}

playlistcontainer::~playlistcontainer()
{
  sp_playlistcontainer_remove_callbacks(pc_, &cb_, this);
  sp_playlistcontainer_release(pc_);
}

bool playlistcontainer::is_loaded() const
{
  return sp_playlistcontainer_is_loaded(pc_);
}

std::vector< playlist_ptr > playlistcontainer::playlists() const {
  std::vector< playlist_ptr > ret;
  int n = sp_playlistcontainer_num_playlists(pc_);
  for (int i = 0; i < n; ++i) {
    ret.push_back(playlist_ptr(new playlist(sp_playlistcontainer_playlist(pc_, i))));
  }
  return ret;
}

void SP_CALLCONV playlistcontainer::cb_playlist_added(sp_playlistcontainer*, sp_playlist *playlist,
                                                      int position, void *userdata) {
  reinterpret_cast< playlistcontainer* >(userdata)->added(playlist, position);
}

void SP_CALLCONV playlistcontainer::cb_playlist_removed(sp_playlistcontainer*, sp_playlist *playlist,
                                                        int position, void *userdata) {
  reinterpret_cast< playlistcontainer* >(userdata)->removed(playlist, position);
}

void SP_CALLCONV playlistcontainer::cb_playlist_moved(sp_playlistcontainer*, sp_playlist *playlist,
                                                      int position, int new_position, void *userdata) {
  reinterpret_cast< playlistcontainer* >(userdata)->moved(playlist, position, new_position);
}

void SP_CALLCONV playlistcontainer::cb_container_loaded(sp_playlistcontainer*, void *userdata) {
  reinterpret_cast< playlistcontainer* >(userdata)->loaded();
}


NS_SPOTIFY_END

