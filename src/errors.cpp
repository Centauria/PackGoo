#include "errors.h"

#include <SDL_error.h>
#include <SDL_image.h>

#include <spdlog/spdlog.h>

SDLError::SDLError()
    : exception(),
      msg(SDL_GetError()) {
    spdlog::error("Error while initializing SDL: {0}", SDL_GetError());
}

SDLError::SDLError(const std::string& m)
    : exception(),
      msg(m) {
    spdlog::error("Error while initializing SDL: {0}", m);
}

SDLError::~SDLError() throw() {
}

const char* SDLError::what() const throw() { return msg.c_str(); }

SDLImgError::SDLImgError()
    : exception(),
      msg(IMG_GetError()) {
    spdlog::error("SDL_image Error: {0}", IMG_GetError());
}

SDLImgError::SDLImgError(const std::string& m)
    : exception(),
      msg(m) {
    spdlog::error("SDL_image Error: {0}", m);
}

SDLImgError::~SDLImgError() throw() {

}

const char* SDLImgError::what() const throw() { return msg.c_str(); }
