package systemUI;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import Operation.*;
import Users.*;

public class SignIn extends JFrame implements ActionListener{

	private static final long serialVersionUID = 1L;

	private User user;
	Font font;
	private JLabel jl;
	private JLabel name, pass;
	private JTextField jt_name;
	private JPasswordField password;
	private JPanel jp_center_left, jp_center_right, jp_center, jp_south;
	private JButton jb1, jb2;

	public SignIn() {

		jl = new JLabel("登录",SwingUtilities.CENTER);
		font = new Font("宋体",Font.BOLD,36);
		jl.setFont(font);
		jl.setBorder(BorderFactory.createEmptyBorder(20, 20, 20,20));
		this.add(jl,BorderLayout.NORTH);

		font = new Font("宋体",Font.PLAIN,24);
		name = new JLabel("用户名：",SwingUtilities.RIGHT);
		name.setFont(font);
		pass = new JLabel("密码：",SwingUtilities.RIGHT);
		pass.setFont(font);

		jp_center_left = new JPanel();		
		jp_center_left.setLayout(new GridLayout(2,1));
		jp_center_left.add(name);
		jp_center_left.add(pass);

		font = new Font("宋体",Font.PLAIN,24);
		jt_name = new JTextField();
		jt_name.setFont(font);
		password = new JPasswordField();
		password.setFont(font);
		password.setEchoChar('*');

		jp_center_right = new JPanel();
		jp_center_right.setLayout(new GridLayout(2,1));
		jp_center_right.add(jt_name);
		jp_center_right.add(password);

		jp_center = new JPanel();
		jp_center.setLayout(new GridLayout(1,2));
		jp_center.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 60));
		jp_center.add(jp_center_left);
		jp_center.add(jp_center_right);

		jb1 = new JButton("确认");
		jb2 = new JButton("返回");
		jb2.addActionListener(this);
		jb1.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					user = Main.search(jt_name.getText(), new String(password.getPassword()));
					if(user.getRole().equals("Administrator")) {
						new AdministratorUI(user);
					}
					else {
						new UserUI(user);
					}
					SignIn.this.dispose();
				} catch(NullPointerException e1) {
					JOptionPane.showMessageDialog(SignIn.this, "用户名或密码错误！", "提示", JOptionPane.INFORMATION_MESSAGE);
				}
			}
		});

		jp_south = new JPanel();
		jp_south.add(jb1);
		jp_south.add(jb2);
		jp_south.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

		this.add(jp_center);
		this.add(jp_south,BorderLayout.SOUTH);
		this.setTitle("档案管理系统");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(400, 260);
		this.setVisible(true);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == jb2) {
			this.setVisible(false);
			new WelcomeUI();
		}
	}
}
