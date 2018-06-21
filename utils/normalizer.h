#ifndef NORMALIZER_H
#define NORMALIZER_H

class Normalizer {
    private:
        void normalize(float *v);
        float * crossProduct(float *a, float *b);
    public:
        Normalizer();
        float * calculateNormal(float *a, float *b, float *c);
};

#endif /* NORMALIZER_H */