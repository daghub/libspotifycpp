#include "playlist.h"
#include "track.h"

NS_SPOTIFY_BEGIN

sp_playlist_callbacks playlist::cb_;


playlist::playlist(sp_playlist* pl) : pl_(pl)
{
  sp_playlist_add_ref(pl_);
  cb_.tracks_added = &cb_tracks_added;
  cb_.tracks_removed = &cb_tracks_removed;
  cb_.tracks_moved = &cb_tracks_moved;
  cb_.playlist_renamed = &cb_playlist_renamed;
  cb_.playlist_state_changed = &cb_playlist_state_changed;
  cb_.playlist_update_in_progress = &cb_playlist_update_in_progress;
  cb_.playlist_metadata_updated = &cb_playlist_metadata_updated;
  cb_.track_created_changed = &cb_track_created_changed;
  cb_.track_seen_changed = &cb_track_seen_changed;
  cb_.description_changed = &cb_description_changed;
  cb_.image_changed = &cb_image_changed;
  cb_.track_message_changed = &cb_track_message_changed;
  cb_.subscribers_changed = &cb_subscribers_changed;
  sp_playlist_add_callbacks(pl_, &cb_, this);
}

playlist::~playlist()
{
  sp_playlist_remove_callbacks(pl_, &cb_, this);
  sp_playlist_release(pl_);
}

bool playlist::is_loaded() const {
  return sp_playlist_is_loaded(pl_);
}

const char* playlist::name() const {
  return sp_playlist_name(pl_);
}

std::vector< track_ptr > playlist::tracks() const {
  std::vector< track_ptr > ret;
  int n = sp_playlist_num_tracks(pl_);
  for (int i = 0; i < n; ++i) {
    ret.push_back(track_ptr(new track(sp_playlist_track(pl_, i))));
  }
  return ret;
}

void SP_CALLCONV playlist::cb_tracks_added(sp_playlist*, sp_track* const* tracks, int num_tracks,
                                           int position, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->tracks_added(tracks, num_tracks, position);
}

void SP_CALLCONV playlist::cb_tracks_removed(sp_playlist*, const int* tracks,
                                             int num_tracks, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->tracks_removed(tracks, num_tracks);
}

void SP_CALLCONV playlist::cb_tracks_moved(sp_playlist*, const int* tracks, int num_tracks,
                                           int new_position, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->tracks_moved(tracks, num_tracks, new_position);
}

void SP_CALLCONV playlist::cb_playlist_renamed(sp_playlist*, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->renamed();
}

void SP_CALLCONV playlist::cb_playlist_state_changed(sp_playlist*, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->state_changed();
}

void SP_CALLCONV playlist::cb_playlist_update_in_progress(sp_playlist*, bool done, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->update_in_progress(done);
}

void SP_CALLCONV playlist::cb_playlist_metadata_updated(sp_playlist*, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->metadata_updated();
}

void SP_CALLCONV playlist::cb_track_created_changed(sp_playlist*, int position, sp_user *user,
                                                    int when, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->track_created_changed(position, user, when);
}

void SP_CALLCONV playlist::cb_track_seen_changed(sp_playlist*, int position,
                                                 bool seen, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->track_seen_changed(position, seen);
}

void SP_CALLCONV playlist::cb_description_changed(sp_playlist *, const char *desc, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->description_changed(desc);
}

void SP_CALLCONV playlist::cb_image_changed(sp_playlist*, const byte *image, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->image_changed(image);
}

void SP_CALLCONV playlist::cb_track_message_changed(sp_playlist*, int position, const char *message,
                                                    void *userdata) {
  reinterpret_cast< playlist* >(userdata)->track_message_changed(position, message);
}

void SP_CALLCONV playlist::cb_subscribers_changed(sp_playlist*, void *userdata) {
  reinterpret_cast< playlist* >(userdata)->subscribers_changed();
}

NS_SPOTIFY_END

