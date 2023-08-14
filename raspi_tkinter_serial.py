import tkinter as tk
import serial
import queue
import threading

class DaminGUI:
    def __init__(self, root, command_queue):
        self.root = root
        self.command_queue = command_queue

        self.root.title("Stepper Motor Control")
        self.root.geometry("400x300")
        self.root.configure(bg="#800000")

        self.connection_status = tk.Label(self.root, text="Arduino Not Connected", fg="red")
        self.connection_status.pack()

        self.create_buttons()

    def create_buttons(self):
        cw_button = tk.Button(self.root, text="CW", command=self.send_cw_command)
        cw_button.pack()

        ccw_button = tk.Button(self.root, text="CCW", command=self.send_ccw_command)
        ccw_button.pack()

        pause_button = tk.Button(self.root, text="Pause/Stop", command=self.send_pause_command)
        pause_button.pack()

    def send_cw_command(self):
        self.command_queue.put("CW")

    def send_ccw_command(self):
        self.command_queue.put("CCW")

    def send_pause_command(self):
        self.command_queue.put("STOP")

def control_motor(command_queue):
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        gui.connection_status.pack_forget()  # Remove connection status label if connected
    except serial.SerialException:
        ser = None  # Arduino not connected

    while True:
        if ser:
            try:
                command = command_queue.get(timeout=0.1)  # Fetch command from the queue
                ser.write(command.encode())
                print(f"Sent command: {command}")
            except queue.Empty:
                pass  # Queue is empty, continue waiting
        else:
            print("Arduino not connected")

if __name__ == "__main__":
    command_queue = queue.Queue()

    root = tk.Tk()
    gui = DaminGUI(root, command_queue)

    motor_thread = threading.Thread(target=control_motor, args=(command_queue,))
    motor_thread.start()

    root.mainloop()
