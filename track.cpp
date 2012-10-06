#include "track.h"

NS_SPOTIFY_BEGIN


track::track(sp_track* track) : track_(track) {
  sp_track_add_ref(track_);
}

track::~track() {
  sp_track_release(track_);
}

bool track::is_loaded() const {
  return sp_track_is_loaded(track_);
}


NS_SPOTIFY_END

