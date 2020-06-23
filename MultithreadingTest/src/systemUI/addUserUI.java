package systemUI;

import java.awt.BorderLayout;
import java.awt.Choice;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import Operation.DataException;
import Users.Administrator;

public class addUserUI extends JFrame implements ActionListener{

	private static final long serialVersionUID = 1L;

	private Font font;
	private JLabel title, jl_name, jl_password, jl_role;
	private JTextField name;
	private JPasswordField password;
	private Choice role;
	private JButton sure,cancel;
	private UserListUI list;

	private Administrator user;

	public addUserUI(Administrator user, UserListUI userlist) {
		this.list = userlist;
		this.user = user;
		font = new Font("宋体", Font.BOLD, 40);
		this.setLayout(new BorderLayout(30, 30));
		title = new JLabel("添加用户", SwingUtilities.CENTER);
		title.setFont(font);
		this.add(title,BorderLayout.NORTH);

		font = new Font("宋体", Font.PLAIN, 28);
		jl_name = new JLabel("请输入用户名：", SwingUtilities.RIGHT);
		jl_name.setFont(font);
		jl_password = new JLabel("请输入密码：", SwingUtilities.RIGHT);
		jl_password.setFont(font);
		jl_role = new JLabel("用户身份：", SwingUtilities.RIGHT);
		jl_role.setFont(font);

		JPanel left = new JPanel();
		left.setLayout(new GridLayout(3,1));
		left.setSize(new Dimension(200, 150));
		left.add(jl_name);
		left.add(jl_password);
		left.add(jl_role);

		name = new JTextField();
		name.setFont(font);
		password = new JPasswordField();
		password.setFont(font);
		password.setEchoChar('*');
		role = new Choice();
		role.add("Administrator");
		role.add("Operator");
		role.add("Browser");
		role.setFont(font);

		JPanel right = new JPanel();
		right.setLayout(new GridLayout(3, 1));
		right.setSize(new Dimension(200, 150));
		right.add(name);
		right.add(password);
		right.add(role);

		JPanel center = new JPanel();
		center.setLayout(new GridLayout(1, 2));
		center.add(left);
		center.add(right);
		this.add(center);

		sure = new JButton("确认");
		sure.setFont(font);
		sure.addActionListener(this);
		cancel = new JButton("取消");
		cancel.setFont(font);
		cancel.addActionListener(this);

		JPanel bottem = new JPanel();
		bottem.setLayout(new FlowLayout());
		bottem.add(sure);
		bottem.add(cancel);
		this.add(bottem, BorderLayout.SOUTH);

		this.pack();
		this.setVisible(true);
		this.setLocationRelativeTo(null);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == cancel) {
			this.dispose();
		}
		else if(e.getSource() == sure) {
			try {
				user.addUser(name.getText(), new String(password.getPassword()), new String(role.getSelectedItem()));
				JOptionPane.showMessageDialog(addUserUI.this, "添加用户成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
				list.addrow(name.getText(), new String(role.getSelectedItem()));
				this.dispose();
			} catch (DataException e1) {
				JOptionPane.showMessageDialog(addUserUI.this, e1.getString(), "提示", JOptionPane.INFORMATION_MESSAGE);
			}
		}
	}
}
