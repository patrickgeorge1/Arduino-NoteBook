using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Joystick_Mouse
{
    public partial class Form1 : Form
    {
        // communication requierments
        public System.IO.Ports.SerialPort port =  new System.IO.Ports.SerialPort();
        public string coordinates;
        public bool status_connection = false;

        // phisics requirements
        public int x_acceleration = 0;
        public int y_acceleration = 0;
        public int x_speed = 0;
        public int y_speed = 0;


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                // Load port names in the combobox
                cPorts.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
                cPorts.SelectedIndex = 0;

                // Prepare port event handler
                port.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(DataReceivedHandler);
            }
            catch {}

        }

        private void bConnect_Click(object sender, EventArgs e)
        {
            try
            {
                if (!status_connection)
                {
                    open_serial_connection();
                }
                else
                {
                    close_serial_connection();
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }

        private void open_serial_connection()
        {
            // change status
            status_connection = true;

            // get serial port name and baud rate
            string portName = cPorts.SelectedItem.ToString();
            int baudRate = 0;
            Int32.TryParse(cBaudRate.SelectedItem.ToString(), out baudRate);

            // set & open port
            port.PortName = portName;
            port.BaudRate = baudRate;
            port.Open();


            // change UI
            lStatus.Text = "Connected";
            lStatus.ForeColor = System.Drawing.Color.Green;
            bConnect.Text = "Disconnect";

            // Cursor.Clip = new Rectangle(this.Location, this.Size);
        }

        private void close_serial_connection()
        {
            // change status
            status_connection = false;

            // close port
            port.Close();


            // change UI
            lStatus.Text = "Disconnected";
            lStatus.ForeColor = System.Drawing.Color.Red;
            lX.Text = "-";
            lY.Text = "-";
            bConnect.Text = "Connect";
        }

        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            if (status_connection)
            {
                coordinates = port.ReadLine();
                this.Invoke(new EventHandler(DisplayAndMoveCursor));
            }
        }

 

        private void DisplayAndMoveCursor(object sender, EventArgs e)
        {
            try
            {
                string[] words = coordinates.Split('#');
                string X = words[0];
                string Y = words[1];


                int x_value = int.Parse(X) / 25;
                int y_value = int.Parse(Y) / 25;

                int x_sign  = Math.Sign(x_value);
                int y_sign  = Math.Sign(y_value);



                x_acceleration = Math.Abs(x_value);
                y_acceleration = Math.Abs(y_value);

                x_speed = x_sign * (Math.Abs(x_speed) + x_acceleration);
                y_speed = y_sign * (Math.Abs(y_speed) + y_acceleration);

                lX.Text = Cursor.Position.X.ToString();
                lY.Text = Cursor.Position.Y.ToString();


                this.Cursor = new Cursor(Cursor.Current.Handle);
                Cursor.Position = new Point(Cursor.Position.X + x_speed, Cursor.Position.Y + y_speed);


            } catch { }
        }
    }


}
