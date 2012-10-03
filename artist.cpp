#include "artist.h"

NS_SPOTIFY_BEGIN

artist::artist(sp_artist* artist) : artist_(artist)
{
  sp_artist_add_ref(artist_);
}

artist::~artist()
{
  sp_artist_release(artist_);
}

const char* artist::name() const
{
  return sp_artist_name(artist_);
}

bool artist::is_loaded() const
{
  return sp_artist_is_loaded(artist_);
}

const byte* artist::portrait(sp_image_size size)
{
  return sp_artist_portrait(artist_, size);
}

NS_SPOTIFY_END
