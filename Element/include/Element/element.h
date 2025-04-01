#ifndef ELEMENT_H
#define ELEMENT_H

#include <algorithm>
#include <string>
#include <system_error>

namespace Tramp {

    class InatureElement;

    class WeakElement {
    private:
        std::shared_ptr<InatureElement> element_;
        double multipleer_;
    public:
        WeakElement() = delete;
        WeakElement(std::shared_ptr<InatureElement> , double );
        ~WeakElement() = default;

        [[nodiscard]] double getMultipleer() const;
        [[nodiscard]] std::shared_ptr<InatureElement> getElement() const;
    };

    class InatureElement {
    public:
        virtual ~InatureElement() = default;

        [[nodiscard]] virtual std::string getName() const = 0;
    };

    class Water : public InatureElement {
    private:
        std::string name_;
    public:
        Water() = delete;
        explicit Water(std::string);
        ~Water() override = default;



        [[nodiscard]] std::string getName() const  override;
    };

    class Fire : public InatureElement {
    private:

        std::string name_;
    public:
        Fire() = delete;
        ~Fire() override = default;
        explicit Fire(std::string);


        [[nodiscard]] std::string getName() const override;
    };
    class Holy: public InatureElement{
    private:
        std::string name_;


    public:
        Holy() = delete;
        ~Holy() override = default;
        explicit Holy(std::string);


        [[nodiscard]] std::string getName() const override;
    };

    class Devil: public InatureElement{
    private:
        std::string name_;
    public:
        Devil() = delete;
        ~Devil() override = default;
        explicit Devil(std::string);


        [[nodiscard]] std::string getName() const override;
    };




}


#endif //ELEMENT_H
