#! python3

import pyautogui
import sys
import time
# import keyboard

global __TWEEN_MOD__
__TWEEN_MOD__ = pyautogui.easeInOutQuad

def reset_homepage():
    """Reset the homepage to the default URL for ac docs."""
    pyautogui.hotkey('ctrl', 'l')  # Focus address bar
    pyautogui.write('https://ibois-epfl.github.io/augmented-carpentry/')
    pyautogui.press('enter')

def scroll(
    start_scrollbar_pos_xy : tuple = (1913, 123),
    end_scrollbar_pos_y : int = 300,
    duration : float = 1) -> tuple:
    """
        Scroll the mouse wheel up and down using the bar on the right.
    
        :param start_scrollbar_pos_xy: The starting position of the scrollbar (x, y).
        :param end_scrollbar_pos_y: The ending position of the scrollbar (y).
        :param duration: The duration of the scroll in seconds.

        :return: The new position of the mous on the scrollbar (x, y).
    """

    pyautogui.moveTo(start_scrollbar_pos_xy[0], start_scrollbar_pos_xy[1])
    pyautogui.mouseDown()
    new_pos_y = end_scrollbar_pos_y - start_scrollbar_pos_xy[1]
    pyautogui.moveRel(0, new_pos_y, duration, __TWEEN_MOD__)
    pyautogui.mouseUp()

    return (start_scrollbar_pos_xy[0], end_scrollbar_pos_y)

def main():
    # Ensure pyautogui has a failsafe
    pyautogui.FAILSAFE = True

    try:
        # Switch to Firefox (Windows alt+tab until Firefox is found)
        pyautogui.hotkey('alt', 'tab')
        speed_mouse_move = 1  # seconds
        
        reset_homepage()
        
        # tools
        pyautogui.moveTo(948, 478)
        pyautogui.moveTo(457, 525, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()
        pyautogui.moveTo(411, 375, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()
        time.sleep(1)
        current_pos = scroll(end_scrollbar_pos_y=513, duration=3)
        time.sleep(1)
        current_pos = scroll(start_scrollbar_pos_xy=current_pos, end_scrollbar_pos_y=950, duration=2)
        time.sleep(1)
        scroll(start_scrollbar_pos_xy=current_pos, end_scrollbar_pos_y=100, duration=0.5)

        # execution model
        pyautogui.moveTo(634, 152, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()
        pyautogui.moveTo(442, 284, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()
        time.sleep(1)
        current_pos = scroll(end_scrollbar_pos_y=434, duration=4)
        time.sleep(1)
        current_pos = scroll(start_scrollbar_pos_xy=current_pos, end_scrollbar_pos_y=900, duration=4)
        time.sleep(1)
        pyautogui.moveTo(431, 300, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()

        # circular saw
        pyautogui.moveTo(1082, 603, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()
        time.sleep(3)
        pyautogui.moveTo(755, 861, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()
        pyautogui.moveTo(692, 910, speed_mouse_move, __TWEEN_MOD__)
        time.sleep(3)
        current_pos = scroll(end_scrollbar_pos_y=344, duration=4)
        time.sleep(2)
        current_pos = scroll(start_scrollbar_pos_xy=current_pos, end_scrollbar_pos_y=530, duration=3)
        time.sleep(1.5)
        current_pos = scroll(start_scrollbar_pos_xy=current_pos, end_scrollbar_pos_y=731, duration=3)
        time.sleep(1.5)
        scroll(start_scrollbar_pos_xy=current_pos, end_scrollbar_pos_y=100, duration=0.5)
        pyautogui.moveTo(780, 156, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()

        # built works
        time.sleep(1)
        current_pos = scroll(end_scrollbar_pos_y=800, duration=11)
        time.sleep(0.5)
        scroll(start_scrollbar_pos_xy=current_pos, end_scrollbar_pos_y=100, duration=0.5)
        pyautogui.moveTo(952, 155, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()

        # developer guide
        time.sleep(1)
        current_pos = scroll(end_scrollbar_pos_y=846, duration=7)
        pyautogui.moveTo(396, 107, speed_mouse_move, __TWEEN_MOD__)
        pyautogui.click()

    except Exception as e:
        print(f'\nError: {e}')
    finally:
        print('\nScript finished.')

if __name__ == '__main__':
    main()