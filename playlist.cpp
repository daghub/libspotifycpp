#include "playlist.h"

NS_SPOTIFY_BEGIN

sp_playlist_callbacks playlist::cb_;


playlist::playlist(sp_playlist* pl) : pl_(pl)
{
  sp_playlist_add_ref(pl_);
  /*  cb_.playlist_added = &cb_playlist_added;
  cb_.playlist_removed = &cb_playlist_removed;
  cb_.playlist_moved = &cb_playlist_moved;
  cb_.container_loaded = &cb_container_loaded; */
  //sp_playlistcontainer_add_callbacks(pc_, &cb_, this);
}

playlist::~playlist()
{
  //  sp_playlist_remove_callbacks(pc_, &cb_, this);
  sp_playlist_release(pl_);
}

bool playlist::is_loaded() const
{
  return sp_playlist_is_loaded(pl_);
}

void SP_CALLCONV playlist::cb_tracks_added(sp_playlist*, sp_track* const* tracks, int num_tracks,
                                           int position, void *userdata) {
}

void SP_CALLCONV playlist::cb_tracks_removed(sp_playlist*, const int* tracks,
                                             int num_tracks, void *userdata) {
}

void SP_CALLCONV playlist::cb_tracks_moved(sp_playlist*, const int* tracks, int num_tracks,
                                           int new_position, void *userdata) {
}

void SP_CALLCONV playlist::cb_playlist_renamed(sp_playlist*, void *userdata) {
}

void SP_CALLCONV playlist::cb_playlist_state_changed(sp_playlist*, void *userdata) {
}

void SP_CALLCONV playlist::cb_playlist_update_in_progress(sp_playlist*, bool done, void *userdata) {
}

void SP_CALLCONV playlist::cb_playlist_metadata_updated(sp_playlist*, void *userdata) {
}

void SP_CALLCONV playlist::cb_track_created_changed(sp_playlist*, int position, sp_user *user,
                                                    int when, void *userdata) {
}
void SP_CALLCONV playlist::cb_track_seen_changed(sp_playlist*, int position,
                                                 bool seen, void *userdata) {
}

void SP_CALLCONV playlist::cb_description_changed(sp_playlist *, const char *desc, void *userdata) {
}

void SP_CALLCONV playlist::cb_image_changed(sp_playlist*, const byte *image, void *userdata) {
}

void SP_CALLCONV playlist::cb_track_message_changed(sp_playlist*, int position, const char *message,
                                                    void *userdata) {
}

void SP_CALLCONV playlist::cb_subscribers_changed(sp_playlist*, void *userdata) {
}

NS_SPOTIFY_END

