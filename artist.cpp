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


NS_SPOTIFY_END
