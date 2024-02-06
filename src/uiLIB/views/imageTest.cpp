#include "main.h"
#include "uiLIB/assets/imageTest.c"
#include "uiLIB/assets/fieldResized.c"
rd::imageTest::imageTest(){
    this->view = rd_view_create("imageTest");
    image = lv_img_create(view->obj);
    lv_img_set_src(image, &fieldResized);
}

void rd::imageTest::focus(){
    rd_view_focus(this->view);
}