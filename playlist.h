#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "base.h"

NS_SPOTIFY_BEGIN

class playlist : boost::noncopyable
{
public:
  ~playlist();

  bool is_loaded() const;

  //sig::signal< void(sp_playlist*, int position) > added;
  //sig::signal< void(sp_playlist*, int position) > removed;
  //sig::signal< void(sp_playlist*, int position, int new_position) > moved;
  //sig::signal< void() > loaded;

private:
  playlist(sp_playlist* pl);

  static void SP_CALLCONV cb_tracks_added(sp_playlist*, sp_track* const* tracks, int num_tracks,
                                          int position, void *userdata);
  static void SP_CALLCONV cb_tracks_removed(sp_playlist*, const int* tracks,
                                            int num_tracks, void *userdata);
  static void SP_CALLCONV cb_tracks_moved(sp_playlist*, const int* tracks, int num_tracks,
                                          int new_position, void *userdata);
  static void SP_CALLCONV cb_playlist_renamed(sp_playlist*, void *userdata);
  static void SP_CALLCONV cb_playlist_state_changed(sp_playlist*, void *userdata);
  static void SP_CALLCONV cb_playlist_update_in_progress(sp_playlist*, bool done, void *userdata);
  static void SP_CALLCONV cb_playlist_metadata_updated(sp_playlist*, void *userdata);
  static void SP_CALLCONV cb_track_created_changed(sp_playlist*, int position, sp_user *user,
                                                   int when, void *userdata);
  static void SP_CALLCONV cb_track_seen_changed(sp_playlist*, int position,
                                                bool seen, void *userdata);
  static void SP_CALLCONV cb_description_changed(sp_playlist *, const char *desc, void *userdata);
  static void SP_CALLCONV cb_image_changed(sp_playlist*, const byte *image, void *userdata);
  static void SP_CALLCONV cb_track_message_changed(sp_playlist*, int position, const char *message,
                                                   void *userdata);
  static void SP_CALLCONV cb_subscribers_changed(sp_playlist*, void *userdata);

  friend class playlistcontainer;

  static sp_playlist_callbacks cb_;
  sp_playlist* pl_;
};

NS_SPOTIFY_END

#endif
