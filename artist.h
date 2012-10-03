#ifndef ARTIST_H
#define ARTIST_H

#include "base.h"

NS_SPOTIFY_BEGIN

class artist : boost::noncopyable
{
public:
  ~artist();
  const char* name() const;

private:
  artist(sp_artist* artist);

  friend class search;

  sp_artist* artist_;
};


NS_SPOTIFY_END

#endif
