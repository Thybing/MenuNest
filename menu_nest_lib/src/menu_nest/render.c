#include "menu_nest/render.h"
#include "menu_nest/common.h"


static void MN_render_empty_rendering_callback(struct MN_render * const self, void * p_param){
    MN_assert(self);
}

MN_render * MN_render_create(void * const p_memory){
    MN_render * new_render = (MN_render *)MN_malloc(sizeof(MN_render));
    if(new_render){
        new_render->mp_memory = p_memory;
        new_render->m_rendering_callback = MN_render_empty_rendering_callback;
        new_render->mp_attribute = NULL;
    }
    return new_render;
}

void MN_render_destroy(MN_render * const self){
    MN_assert(self);

    MN_free(self);
}

void MN_render_set_rendering_callback(MN_render * const self,const rendering_callback_t callback){
    MN_assert(self);

    self->m_rendering_callback = callback;
}

void MN_render_set_attribute(MN_render * const self,void * const p_attribute){
    MN_assert(self);

    self->mp_attribute = p_attribute;
}

void * MN_render_get_attribute(MN_render * const self){
    MN_assert(self);

    return self->mp_attribute;
}

void MN_render_rendering(MN_render * const self, void * const p_render_param){
    MN_assert(self);

    self->m_rendering_callback(self,p_render_param);
}
