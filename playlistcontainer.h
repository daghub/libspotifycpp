#ifndef PLAYLISTCONTAINER_H
#define PLAYLISTCONTAINER_H

#include "base.h"

NS_SPOTIFY_BEGIN

class playlistcontainer : boost::noncopyable
{
public:
  ~playlistcontainer();

  bool is_loaded() const;
  std::vector< playlist_ptr > playlists() const;

  sig::signal< void(sp_playlist*, int position) > added;
  sig::signal< void(sp_playlist*, int position) > removed;
  sig::signal< void(sp_playlist*, int position, int new_position) > moved;
  sig::signal< void() > loaded;

private:
  playlistcontainer(sp_playlistcontainer* pc);

  static void SP_CALLCONV cb_playlist_added(sp_playlistcontainer* pc, sp_playlist* playlist,
                                            int position, void *userdata);
  static void SP_CALLCONV cb_playlist_removed(sp_playlistcontainer* pc, sp_playlist* playlist,
                                              int position, void *userdata);
  static void SP_CALLCONV cb_playlist_moved(sp_playlistcontainer* pc, sp_playlist* playlist,
                                            int position, int new_position, void *userdata);
  static void SP_CALLCONV cb_container_loaded(sp_playlistcontainer* pc, void *userdata);

  friend class session;

  static sp_playlistcontainer_callbacks cb_;
  sp_playlistcontainer* pc_;
};

NS_SPOTIFY_END

#endif
