#include "Uplay.h"

#include <list>

struct Product
{
    Product(uint32_t a, uint32_t b)
    {
        appid = a;
        type = b;
        if (type == 4)
            unknown1 = 4;
        else
            unknown1 = 1;
    }

    uint32_t appid;
    uint32_t type;      // 1 = app, 2 = dlc, 4 = ???
    uint32_t unknown1;  // if (type == 4) 4 else 1
    uint32_t unk_3 = 3; // always 3
    uint32_t unk_0 = 0; // always zero
    uint32_t unk_1 = 1; // always 1
};

struct ProductList
{
    uint32_t number = 0;
    uint32_t padding = 0;
    struct Product** out;
};

DLLEXPORT int UPC_ProductConsume()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_ProductConsumeSignatureFree()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_ProductListFree(ContextData* context, ProductList* in_product_list)
{
    LOGGER_INFO(__FUNCTION__);

    if (in_product_list)
    {
        for (unsigned i = 0; i < in_product_list->number; ++i)
        {
            delete in_product_list->out[i];
        }

        delete[] in_product_list->out;
    }

    delete in_product_list;
    return 0;
}

DLLEXPORT int UPC_ProductListGet(ContextData* context, char* in_opt_user_id_utf8, unsigned in_filter,
                                 ProductList** out_product_list, void* in_callback,
                                 void* in_callback_data) // CB: 1 argument, 0 val
{
    LOGGER_INFO(__FUNCTION__);

    context->callbacks.push(CallbackData(in_callback, in_callback_data, 0));
    std::list<Product> products;
    products.push_back(Product(context->config->GetAppId(), 1));

    unsigned index = 0;
    ProductList* pr_list = new ProductList();
    pr_list->out = new Product*[products.size()];
    for (auto& p : products)
    {
        pr_list->out[index] = new Product(p);
        ++index;
    }

    pr_list->number = index;
    *out_product_list = pr_list;
    return 0x10000;
}