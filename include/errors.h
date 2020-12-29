#include <exception>
#include <string>

class SDLError : public std::exception {
    std::string msg;

public:
    SDLError();
    SDLError(const std::string&);
    virtual ~SDLError() throw();
    const char* what() const throw() override;
};

class SDLImgError : public std::exception {
    std::string msg;

public:
    SDLImgError();
    SDLImgError(const std::string&);
    virtual ~SDLImgError() throw();
    const char* what() const throw() override;
};
