#ifndef HERBE_HPP
#define HERBE_HPP

class Herbe {
private:
    bool presente;
public:
    Herbe();
    bool estPresente() const;
    void setPresente(bool p);
};

#endif