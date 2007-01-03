import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Install extends JApplet implements ActionListener {
	JButton calculate, reset;
	CenterPanel center;

	public void init() {
		try {
			UIManager.setLookAndFeel("com.sun.java.swing.plaf.motif.MotifLookAndFeel");
		} catch(Exception e) { System.out.println("Couldn't load look and feel"); }

		center = new CenterPanel();
		setLayout(new BorderLayout());
		
		calculate = new JButton("Calculate");
		reset = new JButton("Reset");
		calculate.addActionListener(this);
		reset.addActionListener(this);
		
		add(new JLabel("Enter the installment information below"), BorderLayout.NORTH);
		add(center, BorderLayout.CENTER);

		// "Calculate" and "Reset" buttons in subpanel with FlowLayout and center alignment.
		JPanel pSouth = new JPanel();
		pSouth.setLayout(new FlowLayout(FlowLayout.CENTER));
		pSouth.add(calculate);
		pSouth.add(reset);
		add(pSouth, BorderLayout.SOUTH);
	}
	
	public void paint() {

	}
	
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == calculate) {
			double R = center.getCalculation();
			center.setTrueInterestRate(R);
			paint();
		} else if(e.getSource() == reset) {
			center.reset();
		}
	}
}

// Center panel
class CenterPanel extends JPanel {
	ButtonPanel bp;

	JTextField cashPrice;
	JTextField downPayment;
	JTextField carryingCharge;
	JTextField monthlyPayment;
	JTextField interestRate;
	
	public CenterPanel() {
		bp = new ButtonPanel();
	
		cashPrice = new JTextField(20);
		downPayment = new JTextField(20);
		carryingCharge = new JTextField(20);
		monthlyPayment = new JTextField();
		interestRate = new JTextField();
		monthlyPayment.setEnabled(false);
		interestRate.setEnabled(false);
		interestRate.setDisabledTextColor(Color.RED);
	
		setLayout(new GridLayout(6,3,0,10));
		add(new JLabel("Enter Cash Price:"));
		add(cashPrice);
		add(new JLabel("Enter Down Payment:"));
		add(downPayment);
		add(new JLabel("Select Payment Term:"));
		
		add(bp);
		add(new JLabel("Carrying Charge:"));
		add(carryingCharge);
		add(new JLabel("Monthly Payments are:"));
		add(monthlyPayment);		
		add(new JLabel("True Rate of Interest is:"));
		add(interestRate);
	}
	
	public double getCalculation() {
		double R = 0;
		double N = 0;
		double Y = 12;
		double B = 0;
		double C = 0;
		
		// set up our variables
		C = getTextValue(carryingCharge);
		double startCash = getTextValue(cashPrice);
		double lDownPayment = getTextValue(downPayment);
					
		B = startCash - lDownPayment;
			
			
		if(bp.getWhichButton() == 1)
			N = 6;
		else
			N = 12;
		
		double top = B * (N + 1);
		double bottom = 2 * Y * C;
		if(bottom == 0)
			R = 0;
		else
			R = top / bottom ;		
		
		// Do the monthly payment thing
		double moPay = (B + C) / N;
		System.out.println(B + " " + C + " " + N);
		monthlyPayment.setText(String.valueOf(moPay));	
		
		return R;
	}
	
	public void setTrueInterestRate(double R) {
		interestRate.setText(String.valueOf(R));	
	}
	
	private double getTextValue(JTextField j) {
		String i = j.getText();
		try {
			return Double.parseDouble(i);
		} 
		catch(Exception e) { return 0; } // Means it contains alpha characters or blank
	}
	
	public void reset() {
		cashPrice.setText("");
		downPayment.setText("");
		carryingCharge.setText("");
		monthlyPayment.setText("");
		interestRate.setText("");
		bp.reset();
	}
}

// Radio buttons in row 3, column 2 should have FlowLayout manager
// with center alignment.  They should be placed in ButtonGroup
class ButtonPanel extends JPanel implements ActionListener {
	JRadioButton b1;
	JRadioButton b2;

	public ButtonPanel() {
		this.setLayout(new FlowLayout());
		ButtonGroup bg = new ButtonGroup();
		b1 = new JRadioButton("Six months");
		b2 = new JRadioButton("One Year");
		b1.addActionListener(this);
		b2.addActionListener(this);
		b1.setSelected(true);
		bg.add(b1);
		bg.add(b2);
		this.add(b1,BorderLayout.CENTER);
		this.add(b2,BorderLayout.CENTER);
	}
	
	public int getWhichButton() {
		if(b1.isSelected())
			return 1;
		return 2;
	}
	
	public void reset() {
		b1.setSelected(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		if ("Six months".equals(e.getActionCommand())) {
			b1.setSelected(true);
			b2.setSelected(false);
		} else {
			b1.setSelected(false);
			b2.setSelected(true);
		}
	} 
}