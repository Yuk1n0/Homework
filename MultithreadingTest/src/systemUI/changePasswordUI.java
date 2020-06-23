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
import javax.swing.SwingUtilities;

import Operation.DataException;
import Users.User;

public class changePasswordUI extends JFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	private User user;
	private JLabel jl_password, jl_newpassword, jl_check;
	private JPasswordField jt_password, jt_newpassword, jt_check;
	private JPanel left, right, center, south;
	private Font font;
	private JButton sure, cancel;

	public changePasswordUI(User user) {
		this.user = user;

		font = new Font("宋体", Font.PLAIN, 48);
		jl_password = new JLabel("原密码：", SwingUtilities.RIGHT);
		jl_password.setFont(font);
		jl_newpassword = new JLabel("新密码：", SwingUtilities.RIGHT);
		jl_newpassword.setFont(font);
		jl_check = new JLabel("确认新密码：", SwingUtilities.RIGHT);
		jl_check.setFont(font);

		left = new JPanel();
		left.setLayout(new GridLayout(3,1));
		left.add(jl_password);
		left.add(jl_newpassword);
		left.add(jl_check);

		font = new Font("宋体",Font.PLAIN,40);
		jt_password = new JPasswordField();
		jt_password.setFont(font);
		jt_password.setEchoChar('*');
		jt_newpassword = new JPasswordField();
		jt_newpassword.setFont(font);
		jt_newpassword.setEchoChar('*');
		jt_check = new JPasswordField();
		jt_check.setFont(font);
		jt_check.setEchoChar('*');

		right = new JPanel();
		right.setLayout(new GridLayout(3,1));
		right.add(jt_password);
		right.add(jt_newpassword);
		right.add(jt_check);

		center = new JPanel();
		center.setLayout(new GridLayout(1, 2));
		center.add(left);
		center.add(right);

		font = new Font("宋体", Font.BOLD, 28);
		sure = new JButton("确认");
		sure.setFont(font);
		sure.addActionListener(this);
		cancel = new JButton("取消");
		cancel.setFont(font);
		cancel.addActionListener(this);

		south = new JPanel();
		south.setLayout(new GridLayout(1, 2));
		south.add(sure);
		south.add(cancel);
		south.setBorder(BorderFactory.createEmptyBorder(0, 120, 0, 120));

		this.add(center);
		this.add(south,BorderLayout.SOUTH);
		this.setTitle("修改密码");
		this.setVisible(true);
		this.pack();
		this.setResizable(true);
		this.setLocationRelativeTo(null);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == cancel) {
			this.setVisible(false);
		}
		else if(e.getSource() == sure) {
			try {
				user.changeSelfInfo(new String(jt_password.getPassword()), new String(jt_newpassword.getPassword()), new String(jt_check.getPassword()));
				JOptionPane.showMessageDialog(changePasswordUI.this, "修改密码成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
			} catch (DataException e1) {
				JOptionPane.showMessageDialog(changePasswordUI.this, e1.getString(), "提示", JOptionPane.INFORMATION_MESSAGE);
			}
		}
	}
}
