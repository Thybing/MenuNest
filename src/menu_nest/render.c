#include "menu_nest/render.h"
#include "stdlib.h"

MN_render * MN_render_create(const void * const p_memory){
    MN_render * new_render = (MN_render *)malloc(sizeof(MN_render));
    if(new_render){
        new_render->mp_memory = p_memory;
        new_render->m_rendering_callback = NULL;
        new_render->mp_attribute = NULL;
    }
    return new_render;
}

void MN_render_destroy(MN_render * const self){
    free(self);
}

void MN_render_set_rendering_callback(MN_render * const self,const rendering_callback_t callback){
    self->m_rendering_callback = callback;
}

void MN_render_set_attribute(MN_render * const self,void * const p_attribute){
    self->mp_attribute = p_attribute;
}

void * MN_render_get_attribute(MN_render * const self){
    return self->mp_attribute;
}

void MN_render_rendering(MN_render * const self){
    self->m_rendering_callback(self);
}
