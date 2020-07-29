using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;


namespace Control_of_Stepper_Printer
{
    public partial class Form1 : Form
    {
        public Stopwatch watch { get; set; }
        public bool followWatch = false;
        public int position = 0;
        public int delay;

        public Form1()
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            watch = Stopwatch.StartNew();
            port.Open();
        }



        private void tTimer_Tick(object sender, EventArgs e)
        {
            tbSlider.Enabled = true;
            lStatus.Text = "stationary";
            lStatus.ForeColor = Color.Green;
            followWatch = false;
        }


        private void tbSlider_Scroll(object sender, EventArgs e)
        {
            watch = Stopwatch.StartNew();
        }

        private void tChecker_Tick(object sender, EventArgs e)
        {
            if (tbSlider.Value != position && watch.ElapsedMilliseconds > 200)
            {
                // execute
                Console.WriteLine("Move to " + tbSlider.Value.ToString());
                port.Write(String.Format("{0}", tbSlider.Value));

                // sleep
                delay = Math.Abs(tbSlider.Value - position) * 3;
                lStatus.Text = "moving";
                lStatus.ForeColor = Color.Red;
                position = tbSlider.Value;
                tbSlider.Enabled = false;
                tCooldown.Interval = delay + 1;
                
                Console.WriteLine("delay " + delay);
                followWatch = true;
            }
        }
    }
}
