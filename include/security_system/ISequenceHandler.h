#ifndef ISEQUENCE_HANDLER_H
#define ISEQUENCE_HANDLER_H

// Olay türlerini temsil eden basit bir enum (örneðin kamera hareketi)
enum class SecurityEvent { MotionDetected };

class ISequenceHandler {
public:
    // Sanal yýkýcý bellek sýzýntýsýný önler.
    virtual ~ISequenceHandler() = default;

    // Bir sonraki iþleyiciyi ayarlama metodu
    virtual ISequenceHandler* setNext(ISequenceHandler* next) = 0;

    // Ýsteði (olayý) iþleme metodu
    virtual void handleRequest(SecurityEvent event) = 0;

protected:
    // Bir sonraki iþleyiciyi tutacak pointer
    ISequenceHandler* nextHandler = nullptr;
};

#endif // ISEQUENCE_HANDLER_H