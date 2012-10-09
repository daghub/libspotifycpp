#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "base.h"

NS_SPOTIFY_BEGIN

class playlist : boost::noncopyable
{
public:
  ~playlist();

  bool is_loaded() const;
  const char* name() const;
  std::vector< track_ptr > tracks() const;

  sig::signal< void(sp_track* const* tracks, int num_tracks, int position) > tracks_added;
  sig::signal< void(const int* tracks, int num_tracks) > tracks_removed;
  sig::signal< void(const int* tracks, int num_tracks, int new_position) > tracks_moved;
  sig::signal< void() > renamed;
  sig::signal< void() > state_changed;
  sig::signal< void(bool done) > update_in_progress;
  sig::signal< void() > metadata_updated;
  sig::signal< void(int position, sp_user *user, int when) > track_created_changed;
  sig::signal< void(int position, bool seen) > track_seen_changed;
  sig::signal< void(const char *desc) > description_changed;
  sig::signal< void(const byte *image) > image_changed;
  sig::signal< void(int position, const char *message) > track_message_changed;
  sig::signal< void() > subscribers_changed;

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
