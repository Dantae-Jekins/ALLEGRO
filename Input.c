#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

int main()
{
    ALLEGRO_DISPLAY* Screen = NULL;
    ALLEGRO_EVENT_QUEUE* EventQueue = NULL;
    ALLEGRO_EVENT Event;
    ALLEGRO_BITMAP* Background = NULL, * KeyDownImage = NULL;
    bool Exit = false, KeyDown = false;

    if (!al_init())
    {
        al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if (!al_init_image_addon())
    {
        al_show_native_message_box(NULL, "Error!", "Image addon has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    Screen = al_create_display(800, 600);
    if (Screen == NULL)
    {
        al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    EventQueue = al_create_event_queue();
    if (EventQueue == NULL)
    {
        al_show_native_message_box(Screen, "Error!", "Failed to create the event queue.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if (!al_install_keyboard()) ///setup the keyboard
    {
        al_show_native_message_box(NULL, "Error!", "Failed to install keyboard.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_register_event_source(EventQueue, al_get_display_event_source(Screen));
    al_register_event_source(EventQueue, al_get_keyboard_event_source()); ///Tell allegro to get events from the keyboard

    Background = al_load_bitmap("Background.png");
    if (Background == NULL)
    {
        al_show_native_message_box(Screen, "Error!", "Failed to load -Background.png-", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    KeyDownImage = al_load_bitmap("KeyPressed.png");
    if (KeyDownImage == NULL)
    {
        al_show_native_message_box(Screen, "Error!", "Failed to load -KeyPressed.png-", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    while (Exit == false)
    {
        if (KeyDown == true)
        {
            al_draw_bitmap(KeyDownImage, 0, 0, 0);
        }

        else
        {
            al_draw_bitmap(Background, 0, 0, 0);
        }

        al_flip_display();

        al_wait_for_event(EventQueue, &Event);

        if (Event.type == ALLEGRO_EVENT_KEY_DOWN) ///look for keyboard events
        {
            if (Event.keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                KeyDown = true;
            }
        }

        if (Event.type == ALLEGRO_EVENT_KEY_UP)
        {
            KeyDown = false;
        }

        if (Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            Exit = true;
        }
    }

    al_destroy_bitmap(Background);
    al_destroy_bitmap(KeyDownImage);
    al_destroy_event_queue(EventQueue);
    al_destroy_display(Screen);

    return 0;
}
