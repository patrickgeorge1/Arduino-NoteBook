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
        public System.IO.Ports.SerialPort port =  new System.IO.Ports.SerialPort();
        public string coordinates;
        public bool status_connection = false;

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


                int x_difference = int.Parse(X) / 10;
                int y_difference = int.Parse(Y) / 10;


                int x_steps = (int)Math.Sqrt(Math.Abs(x_difference));
                int y_steps = (int)Math.Sqrt(Math.Abs(y_difference));

                int x_step = x_difference / Math.Max(x_steps, y_steps);
                int y_step = y_difference / Math.Max(x_steps, y_steps);

                this.Cursor = new Cursor(Cursor.Current.Handle);

                for (int i = 1; i <= Math.Max(x_steps, y_steps); i++)
                {
                    
                    lX.Text = Cursor.Position.X.ToString();
                    lY.Text = Cursor.Position.Y.ToString();

                    Cursor.Position = new Point(Cursor.Position.X + x_step, Cursor.Position.Y + y_step);
                }

            } catch { }
        }
    }


}
