package Week8;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Random;

public class JNIDemo extends JFrame {

    private static final int RAND_BOUNDS = 100;
    private static final JLabel promptLabel = new JLabel("Enter the number of samples to generate: ");
    private static final JLabel errLabel = new JLabel("Value entered was not valid. Please try again...");
    private static final int WIN_WIDTH = 900;
    private static final int WIN_HEIGHT = 500;
    private enum ExitStatuses { GT_ZERO, INVALID, SUCCESS }

    private static double mean, stdDev;
    private static int[] randomValues;
    private static JLabel meanLabel, stdDevLabel;
    private static ExitStatuses status;


    //Load dynamic library
    static {
        try {
            System.load("/home/neil/devel/IdeaProjects/Lab8_CPP/src/Week8/Week8_JNIDemo.so");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("JNI .so failed to load.\n" + e);
            System.exit(1);
        }
    }

    //Native C++ Function Declarations
    public native double calculateMean(int[] numbers);
    public native double calculateSTDDev(int[] numbers, double mean);

    public JNIDemo() {

        super("Neil Kingdom Lab 8 - JNI Demo");
        Random rand = new Random();
        JButton button = new JButton("Submit");
        JTextField textField = new JTextField();
        meanLabel = new JLabel();
        stdDevLabel = new JLabel();

        //Set Layout
        JPanel mainPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.weightx = 0.2;
        gbc.weighty = 0.2;

        //Component Listeners
        button.addActionListener(actionEvent -> {
            status = submitUserInput(textField.getText());

            if(status == ExitStatuses.SUCCESS) {
                //Generate array of random values
                int inputAsInt = Integer.valueOf(textField.getText());
                randomValues = new int[inputAsInt];
                for(int i = 0; i < randomValues.length; i++)
                    randomValues[i] = rand.nextInt(RAND_BOUNDS);

                //Call Native C++ Functions
                mean = calculateMean(randomValues);
                stdDev = calculateSTDDev(randomValues, mean);
                System.out.println(calculateMean(randomValues));
                System.out.println(calculateSTDDev(randomValues, mean));
                meanLabel.setText("Mean is: " + mean);
                stdDevLabel.setText("Standard Deviation is: " + stdDev);

                meanLabel.setVisible(true);
                stdDevLabel.setVisible(true);
                errLabel.setVisible(false);

                revalidate();
                repaint();
            }
            else if(status == ExitStatuses.GT_ZERO) {
                errLabel.setText("Input must be greater than 0");
                errLabel.setVisible(true);
            }
            else {
                errLabel.setText("Input was not a proper integer value.");
                errLabel.setVisible(true);
            }

            textField.setText("");
        });

        //Component configuration
        errLabel.setForeground(Color.RED);
        errLabel.setVisible(false);

        meanLabel.setVisible(false);
        meanLabel.setForeground(Color.BLUE);
        stdDevLabel.setForeground(Color.BLUE);
        stdDevLabel.setVisible(false);

        textField.setPreferredSize(new Dimension(600, 40));

        //Add Components
        Insets labelInsets = new Insets(0, 60, 0, 0);

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 4;
        gbc.gridheight = 1;
        gbc.weightx = 0.2;
        gbc.weighty = 0.2;
        gbc.insets = labelInsets;
        gbc.anchor = GridBagConstraints.WEST;
        mainPanel.add(promptLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 4;
        gbc.gridheight = 1;
        gbc.weightx = 0.2;
        gbc.weighty = 0.2;
        gbc.insets = labelInsets;
        gbc.anchor = GridBagConstraints.WEST;
        mainPanel.add(errLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.gridwidth = 6;
        gbc.gridheight = 1;
        gbc.weightx = 1;
        gbc.weighty = 1;
        gbc.insets = new Insets(0,0,0,0);
        gbc.anchor = GridBagConstraints.CENTER;
        mainPanel.add(textField, gbc);

        gbc.gridx = 2;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        gbc.gridheight = 1;
        gbc.weightx = 1;
        gbc.weighty = 1;
        gbc.insets = new Insets(0,0,0,0);
        gbc.anchor = GridBagConstraints.CENTER;
        mainPanel.add(button, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.gridwidth = 4;
        gbc.gridheight = 1;
        gbc.weightx = 0.2;
        gbc.weighty = 0.2;
        gbc.insets = labelInsets;
        gbc.anchor = GridBagConstraints.WEST;
        mainPanel.add(meanLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 5;
        gbc.gridwidth = 4;
        gbc.gridheight = 1;
        gbc.weightx = 0.2;
        gbc.weighty = 0.2;
        gbc.insets = labelInsets;
        gbc.anchor = GridBagConstraints.WEST;
        mainPanel.add(stdDevLabel, gbc);

        add(mainPanel);

        //Initialize
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setPreferredSize(new Dimension(WIN_WIDTH, WIN_HEIGHT));
        pack();
        setResizable(false);
        setVisible(true);
    }

    public ExitStatuses submitUserInput(String usrInput) {

        int intInput;

        try {
            intInput = Integer.parseInt(usrInput);
            if(intInput <= 0)
                return ExitStatuses.GT_ZERO;
        } catch (NumberFormatException | InputMismatchException e) {
            return ExitStatuses.INVALID;
        }
        return ExitStatuses.SUCCESS;
    }

    public static void main(String[] args) {
        //Call GUI
        EventQueue.invokeLater(() -> {
            try {
                new JNIDemo();
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
}
