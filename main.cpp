#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>

#include "./CustomVector.hpp"
#include "./CustomList.hpp"
#include "./CustomForwardList.hpp"

template<typename IteratorType>
void display_container(CustomContainer<int, IteratorType>& container) {
    for (auto iter = container.begin(); iter != container.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

template<typename IteratorType>
void fill_container(CustomContainer<int, IteratorType>& container, const int min = 0, const int max = 10, const size_t size = 10) {
    for (int i = 0; i < size; ++i) {
        int value = rand() % (max - min + 1) + min;
        container.push_back(value);
    }
}

template<typename IteratorType>
void observe_functionality(CustomContainer<int, IteratorType>& container) {
    const size_t max_size = 10;
    const int min = 0;
    const int max = 10;
    // fill_container(container, min, max, max_size);
    display_container(container);
    std::cout << std::endl;

    const size_t deleted_index = rand() % max_size;
    std::cout << "delete from vector " << deleted_index << " element"  << std::endl;
    container.erase(deleted_index);
    std::cout << "Updated vector " << container.size() <<  std::endl;
    display_container(container);
    std::cout << std::endl;

    const size_t inserted_index = rand() % max_size;
    std::cout << "insert to vector " << inserted_index << " element "  << std::endl;
    container.insert(rand() % (max - min + 1) + min, inserted_index);
    std::cout << "Updated vector " << container.size() << std::endl;
    display_container(container);
    std::cout << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;
}

int main() {
    srand(time(0));
    //FIXME я понимаю что это костыль, но как сделать так, чтобы вынести в отдельный метод строчки с 59-64, не могу придумать, т.е вынести чтобы не дублировать схожий функционал для разных инстанцев
    const size_t max_size = 10;
    const int min = 0;
    const int max = 10;
    std::cout << std::endl;
    std::cout << "Vector" << std::endl;
    CustomVector<int> custom_vector{2.0};
    fill_container(custom_vector, min, max, max_size);
    CustomVector<int> custom_vector_2 = custom_vector;
    CustomVector<int> custom_vector_3;
    custom_vector_3 = custom_vector_2;
    CustomVector<int> custom_vector_4(std::move(custom_vector_3));
    CustomVector<int> custom_vector_5;
    custom_vector_5 = std::move(custom_vector_4);
    observe_functionality(custom_vector_5);

    std::cout << "List" << std::endl;
    CustomList<int> custom_list;
    fill_container(custom_list, min, max, max_size);
    CustomList<int> custom_list_2 = custom_list;
    CustomList<int> custom_list_3;
    custom_list_3 = custom_list_2;
    CustomList<int> custom_list_4(std::move(custom_list_3));
    CustomList<int> custom_list_5;
    custom_list_5 = std::move(custom_list_4);
    observe_functionality(custom_list_5);

    std::cout << "Forward List" << std::endl;
    CustomForwardList<int> custom_forward_list;
    fill_container(custom_forward_list, min, max, max_size);
    CustomForwardList<int> custom_forward_list_2 = custom_forward_list;
    CustomForwardList<int> custom_forward_list_3;
    custom_forward_list_3 = custom_forward_list_2;
    CustomForwardList<int> custom_forward_list_4(std::move(custom_forward_list_3));
    CustomForwardList<int> custom_forward_list_5;
    custom_forward_list_5 = std::move(custom_forward_list_4);
    observe_functionality(custom_forward_list_5);
    return 0;
}