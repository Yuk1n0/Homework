package systemUI;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class WelcomeUI extends JFrame implements ActionListener{

	private static final long serialVersionUID = 1L;

	private JLabel welcome;
	private JButton signin, exit;

	public WelcomeUI() {
		welcome = new JLabel("欢迎使用档案管理系统v2.0.2", SwingUtilities.CENTER);
		Font font = new Font("宋体",Font.BOLD,26);
		welcome.setFont(font);
		welcome.setBorder(BorderFactory.createEmptyBorder(20, 20, 20,20));	//设置组件边框	

		font = new Font("宋体",Font.BOLD,28);
		signin = new JButton("登录");
		exit = new JButton("退出");
		signin.setBackground(Color.WHITE);
		signin.setFont(font);
		exit.setBackground(Color.WHITE);
		exit.setFont(font);

		signin.addActionListener(this);
		exit.addActionListener(this);

		JPanel jp_center = new JPanel();
		jp_center.setLayout(new GridLayout(2,1));
		jp_center.setBorder(BorderFactory.createEmptyBorder(30, 130, 30, 130));
		jp_center.add(signin);
		jp_center.add(exit);

		this.add(welcome,BorderLayout.NORTH);
		this.add(jp_center,BorderLayout.CENTER);
		this.setTitle("档案管理系统");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		this.setSize(400, 260);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == signin) {
			this.dispose();
			new SignIn();
		}
		else if(e.getSource() == exit) {
			System.exit(0);
		}
	}
}
