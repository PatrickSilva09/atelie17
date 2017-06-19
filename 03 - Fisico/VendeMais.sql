-- phpMyAdmin SQL Dump
-- version 4.1.12
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jun 19, 2017 at 04:42 AM
-- Server version: 5.5.36
-- PHP Version: 5.4.27

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `merceariafatima`
--
CREATE DATABASE IF NOT EXISTS `merceariafatima` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `merceariafatima`;

-- --------------------------------------------------------

--
-- Table structure for table `cliente`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `cliente`;
CREATE TABLE IF NOT EXISTS `cliente` (
  `idCliente` int(11) NOT NULL AUTO_INCREMENT,
  `cpf` char(11) DEFAULT NULL,
  `nome` varchar(45) NOT NULL,
  `dataNascimento` date DEFAULT NULL,
  `limiteCredito` float NOT NULL DEFAULT '200',
  PRIMARY KEY (`idCliente`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `cliente`
--

INSERT INTO `cliente` (`idCliente`, `cpf`, `nome`, `dataNascimento`, `limiteCredito`) VALUES
(1, '12312312310', 'Cliente 1', '1980-02-22', 200),
(2, '12312312311', 'Cliente 2', '1990-01-10', 200),
(3, '12312312312', 'Cliente 3', '1990-10-15', 200),
(4, '12312312313', 'Cliente 4', '1978-02-28', 200),
(5, '12312312314', 'Cliente 5', '1973-10-05', 200);

-- --------------------------------------------------------

--
-- Table structure for table `compra`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `compra`;
CREATE TABLE IF NOT EXISTS `compra` (
  `idCompra` int(11) NOT NULL AUTO_INCREMENT,
  `fkFornecedor` int(11) NOT NULL,
  `fkNotaFiscal` int(11) NOT NULL,
  `fkFuncionario` int(11) NOT NULL,
  `dataCompra` date NOT NULL,
  `valor` float NOT NULL,
  PRIMARY KEY (`idCompra`),
  KEY `fk_compra_fornecedor1_idx` (`fkFornecedor`),
  KEY `fk_compra_notaFiscal1_idx` (`fkNotaFiscal`),
  KEY `fk_compra_funcionario1_idx` (`fkFuncionario`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `compra`
--

INSERT INTO `compra` (`idCompra`, `fkFornecedor`, `fkNotaFiscal`, `fkFuncionario`, `dataCompra`, `valor`) VALUES
(1, 1, 1, 1, '2017-06-17', 495.6),
(2, 2, 2, 2, '2017-06-10', 327.6);

-- --------------------------------------------------------

--
-- Table structure for table `fornecedor`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `fornecedor`;
CREATE TABLE IF NOT EXISTS `fornecedor` (
  `idFornecedor` int(11) NOT NULL AUTO_INCREMENT,
  `cnpj` char(15) NOT NULL,
  `nomeFantasia` varchar(45) NOT NULL,
  `cep` char(8) NOT NULL,
  `cidade` varchar(45) NOT NULL,
  `bairro` varchar(45) NOT NULL,
  `rua` varchar(45) NOT NULL,
  `numero` int(11) NOT NULL,
  `email` varchar(45) DEFAULT NULL,
  `responsavel` varchar(45) NOT NULL,
  PRIMARY KEY (`idFornecedor`),
  UNIQUE KEY `cnpj_UNIQUE` (`cnpj`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `fornecedor`
--

INSERT INTO `fornecedor` (`idFornecedor`, `cnpj`, `nomeFantasia`, `cep`, `cidade`, `bairro`, `rua`, `numero`, `email`, `responsavel`) VALUES
(1, '123412341234100', 'Distibuidora ABC', '39800000', 'Belo Horizonte', 'Centro', 'Rua Central', 1000, NULL, 'Joao Silva'),
(2, '123412341234101', 'Distibuidora XYZ', '39800001', 'Teofilo Otoni', 'Ipiranga', 'Avenida Luiz Boali', 100, NULL, 'Maria Cunha');

-- --------------------------------------------------------

--
-- Table structure for table `funcionario`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `funcionario`;
CREATE TABLE IF NOT EXISTS `funcionario` (
  `idFuncionario` int(11) NOT NULL AUTO_INCREMENT,
  `cpf` char(11) NOT NULL,
  `nome` varchar(45) NOT NULL,
  `cargo` varchar(40) NOT NULL,
  PRIMARY KEY (`idFuncionario`),
  UNIQUE KEY `cpf_UNIQUE` (`cpf`),
  UNIQUE KEY `cargo_UNIQUE` (`cargo`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `funcionario`
--

INSERT INTO `funcionario` (`idFuncionario`, `cpf`, `nome`, `cargo`) VALUES
(1, '12312312310', 'Augusto Santos', 'Vendedor'),
(2, '12312312311', 'Josemar Silva', 'Gerente');

-- --------------------------------------------------------

--
-- Table structure for table `logins`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `logins`;
CREATE TABLE IF NOT EXISTS `logins` (
  `fkFuncionario` int(11) NOT NULL,
  `user` varchar(20) NOT NULL,
  `passwd` char(5) NOT NULL,
  PRIMARY KEY (`fkFuncionario`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `logins`
--

INSERT INTO `logins` (`fkFuncionario`, `user`, `passwd`) VALUES
(1, 'augusto', '12345'),
(2, 'josemar', '12345');

-- --------------------------------------------------------

--
-- Table structure for table `notafiscal`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `notafiscal`;
CREATE TABLE IF NOT EXISTS `notafiscal` (
  `numero` int(11) NOT NULL,
  `fkFornecedor` int(11) NOT NULL,
  `dataVencimento` date NOT NULL,
  `valor` float NOT NULL,
  PRIMARY KEY (`numero`),
  KEY `fk_notaFiscal_fornecedor1` (`fkFornecedor`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `notafiscal`
--

INSERT INTO `notafiscal` (`numero`, `fkFornecedor`, `dataVencimento`, `valor`) VALUES
(1, 1, '2017-07-17', 495.6),
(2, 2, '2017-07-10', 327.6);

-- --------------------------------------------------------

--
-- Table structure for table `notinha`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `notinha`;
CREATE TABLE IF NOT EXISTS `notinha` (
  `fkVenda` int(11) NOT NULL,
  `fkCliente` int(11) NOT NULL,
  `dataVencimento` date NOT NULL,
  `status` char(1) NOT NULL,
  PRIMARY KEY (`fkVenda`,`fkCliente`),
  KEY `fk_notinha_cliente1_idx` (`fkCliente`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `notinha`
--

INSERT INTO `notinha` (`fkVenda`, `fkCliente`, `dataVencimento`, `status`) VALUES
(1, 1, '2017-06-14', 's'),
(2, 2, '2017-06-16', 'n'),
(3, 3, '2017-07-15', 's'),
(4, 4, '2017-08-17', 'n'),
(5, 5, '2017-07-14', 'n');

-- --------------------------------------------------------

--
-- Table structure for table `precoproduto`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `precoproduto`;
CREATE TABLE IF NOT EXISTS `precoproduto` (
  `fkProduto` int(11) NOT NULL,
  `preco` float NOT NULL,
  PRIMARY KEY (`fkProduto`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `precoproduto`
--

INSERT INTO `precoproduto` (`fkProduto`, `preco`) VALUES
(1, 11.8),
(2, 5.1),
(3, 3.8),
(4, 2.9),
(5, 2.8),
(6, 1.6),
(7, 2.4),
(8, 3.5),
(9, 1.9),
(12, 5);

-- --------------------------------------------------------

--
-- Table structure for table `produto`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `produto`;
CREATE TABLE IF NOT EXISTS `produto` (
  `idProduto` int(11) NOT NULL AUTO_INCREMENT,
  `codigo` char(13) NOT NULL,
  `descricao` text NOT NULL,
  PRIMARY KEY (`idProduto`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=13 ;

--
-- Dumping data for table `produto`
--

INSERT INTO `produto` (`idProduto`, `codigo`, `descricao`) VALUES
(1, '1231231231230', 'Arroz'),
(2, '1231231231231', 'Feijao'),
(3, '1231231231232', 'Macarrao'),
(4, '1231231231233', 'Farinha'),
(5, '1231231231234', 'Trigo'),
(6, '1231231231235', 'Pipoca'),
(7, '1231231231236', 'Fosforo'),
(8, '1231231231237', 'Vela'),
(9, '1231231231238', 'Bolacha'),
(12, '1000100010001', 'oleo de soja');

-- --------------------------------------------------------

--
-- Table structure for table `produtocompra`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `produtocompra`;
CREATE TABLE IF NOT EXISTS `produtocompra` (
  `fkCompra` int(11) NOT NULL,
  `fkProduto` int(11) NOT NULL,
  `quantidade` int(11) NOT NULL,
  `precoUnidade` float NOT NULL,
  PRIMARY KEY (`fkCompra`,`fkProduto`),
  KEY `fk_produtoCompra_compra1_idx` (`fkCompra`),
  KEY `fk_produtoCompra_produto1` (`fkProduto`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `produtocompra`
--

INSERT INTO `produtocompra` (`fkCompra`, `fkProduto`, `quantidade`, `precoUnidade`) VALUES
(1, 1, 30, 8.26),
(1, 2, 10, 3.57),
(1, 3, 20, 2.66),
(1, 4, 30, 2.03),
(1, 5, 50, 1.96),
(2, 6, 35, 1.12),
(2, 7, 40, 1.68),
(2, 8, 55, 2.45),
(2, 9, 65, 1.33);

-- --------------------------------------------------------

--
-- Table structure for table `produtoestoque`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `produtoestoque`;
CREATE TABLE IF NOT EXISTS `produtoestoque` (
  `fkProduto` int(11) NOT NULL,
  `quantidadeEstoque` int(11) NOT NULL,
  PRIMARY KEY (`fkProduto`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `produtoestoque`
--

INSERT INTO `produtoestoque` (`fkProduto`, `quantidadeEstoque`) VALUES
(1, 30),
(2, 10),
(3, 20),
(4, 30),
(5, 50),
(6, 35),
(7, 40),
(8, 55),
(9, 65),
(12, 0);

-- --------------------------------------------------------

--
-- Table structure for table `produtovenda`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `produtovenda`;
CREATE TABLE IF NOT EXISTS `produtovenda` (
  `fkVenda` int(11) NOT NULL,
  `fkProduto` int(11) NOT NULL,
  `quantidade` int(11) NOT NULL,
  `precoUnidade` float NOT NULL,
  PRIMARY KEY (`fkVenda`,`fkProduto`),
  KEY `fk_venda_has_produto_produto1_idx` (`fkProduto`),
  KEY `fk_venda_has_produto_venda1_idx` (`fkVenda`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `produtovenda`
--

INSERT INTO `produtovenda` (`fkVenda`, `fkProduto`, `quantidade`, `precoUnidade`) VALUES
(1, 1, 4, 11.8),
(1, 4, 3, 2.9),
(1, 7, 1, 2.4),
(2, 1, 7, 11.8),
(2, 2, 9, 5.1),
(2, 9, 1, 1.9),
(3, 2, 2, 5.1),
(3, 3, 1, 3.8),
(3, 7, 7, 2.4),
(3, 8, 8, 3.5),
(4, 1, 2, 11.8),
(4, 2, 5, 5.1),
(5, 1, 2, 11.8),
(5, 2, 2, 5.1),
(5, 3, 1, 3.8),
(5, 4, 3, 2.9),
(5, 5, 5, 2.9),
(5, 6, 1, 1.6),
(5, 7, 7, 2.4);

-- --------------------------------------------------------

--
-- Table structure for table `telefonescliente`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `telefonescliente`;
CREATE TABLE IF NOT EXISTS `telefonescliente` (
  `fkCliente` int(11) NOT NULL,
  `telefone` char(11) NOT NULL,
  PRIMARY KEY (`fkCliente`,`telefone`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `telefonescliente`
--

INSERT INTO `telefonescliente` (`fkCliente`, `telefone`) VALUES
(1, '33556610'),
(1, '33556611'),
(1, '33556612'),
(2, '33556613'),
(2, '33556614'),
(3, '33556615'),
(3, '33556618'),
(4, '33556616'),
(5, '33556617'),
(5, '35276398');

-- --------------------------------------------------------

--
-- Table structure for table `telefonesfornecedor`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `telefonesfornecedor`;
CREATE TABLE IF NOT EXISTS `telefonesfornecedor` (
  `fkFornecedor` int(11) NOT NULL,
  `numero` char(11) NOT NULL,
  PRIMARY KEY (`fkFornecedor`,`numero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `telefonesfornecedor`
--

INSERT INTO `telefonesfornecedor` (`fkFornecedor`, `numero`) VALUES
(1, '33112200'),
(2, '33112201');

-- --------------------------------------------------------

--
-- Table structure for table `venda`
--
-- Creation: Jun 17, 2017 at 09:23 AM
--

DROP TABLE IF EXISTS `venda`;
CREATE TABLE IF NOT EXISTS `venda` (
  `idVenda` int(11) NOT NULL AUTO_INCREMENT,
  `fkCliente` int(11) NOT NULL,
  `fkFuncionario` int(11) NOT NULL,
  `dataVenda` date NOT NULL,
  `valor` float NOT NULL,
  PRIMARY KEY (`idVenda`),
  KEY `fk_venda_cliente1_idx` (`fkCliente`),
  KEY `fk_venda_funcionario1_idx` (`fkFuncionario`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `venda`
--

INSERT INTO `venda` (`idVenda`, `fkCliente`, `fkFuncionario`, `dataVenda`, `valor`) VALUES
(1, 1, 1, '2017-06-14', 58.3),
(2, 2, 2, '2017-06-16', 130.4),
(3, 3, 1, '2017-06-15', 58.8),
(4, 4, 2, '2017-06-17', 49.1),
(5, 5, 2, '2017-06-14', 79.2);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `compra`
--
ALTER TABLE `compra`
  ADD CONSTRAINT `fk_compra_fornecedor1` FOREIGN KEY (`fkFornecedor`) REFERENCES `fornecedor` (`idFornecedor`) ON DELETE NO ACTION ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_compra_funcionario1` FOREIGN KEY (`fkFuncionario`) REFERENCES `funcionario` (`idFuncionario`) ON DELETE NO ACTION ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_compra_notaFiscal1` FOREIGN KEY (`fkNotaFiscal`) REFERENCES `notafiscal` (`numero`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `logins`
--
ALTER TABLE `logins`
  ADD CONSTRAINT `fk_logins_funcionario1` FOREIGN KEY (`fkFuncionario`) REFERENCES `funcionario` (`idFuncionario`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `notafiscal`
--
ALTER TABLE `notafiscal`
  ADD CONSTRAINT `fk_notaFiscal_fornecedor1` FOREIGN KEY (`fkFornecedor`) REFERENCES `fornecedor` (`idFornecedor`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `notinha`
--
ALTER TABLE `notinha`
  ADD CONSTRAINT `fk_notinha_cliente1` FOREIGN KEY (`fkCliente`) REFERENCES `cliente` (`idCliente`) ON DELETE NO ACTION ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_notinha_venda1` FOREIGN KEY (`fkVenda`) REFERENCES `venda` (`idVenda`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `precoproduto`
--
ALTER TABLE `precoproduto`
  ADD CONSTRAINT `fk_precoProduto_produto1` FOREIGN KEY (`fkProduto`) REFERENCES `produto` (`idProduto`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `produtocompra`
--
ALTER TABLE `produtocompra`
  ADD CONSTRAINT `fk_produtoCompra_compra1` FOREIGN KEY (`fkCompra`) REFERENCES `compra` (`idCompra`) ON DELETE NO ACTION ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_produtoCompra_produto1` FOREIGN KEY (`fkProduto`) REFERENCES `produto` (`idProduto`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `produtoestoque`
--
ALTER TABLE `produtoestoque`
  ADD CONSTRAINT `fk_produtoEstoque_produto1` FOREIGN KEY (`fkProduto`) REFERENCES `produto` (`idProduto`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `produtovenda`
--
ALTER TABLE `produtovenda`
  ADD CONSTRAINT `fk_venda_has_produto_produto1` FOREIGN KEY (`fkProduto`) REFERENCES `produto` (`idProduto`) ON DELETE NO ACTION ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_venda_has_produto_venda1` FOREIGN KEY (`fkVenda`) REFERENCES `venda` (`idVenda`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `telefonescliente`
--
ALTER TABLE `telefonescliente`
  ADD CONSTRAINT `fk_telefonesCliente_cliente1` FOREIGN KEY (`fkCliente`) REFERENCES `cliente` (`idCliente`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `telefonesfornecedor`
--
ALTER TABLE `telefonesfornecedor`
  ADD CONSTRAINT `fk_telefonesFornecedor_fornecedor1` FOREIGN KEY (`fkFornecedor`) REFERENCES `fornecedor` (`idFornecedor`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `venda`
--
ALTER TABLE `venda`
  ADD CONSTRAINT `fk_venda_cliente1` FOREIGN KEY (`fkCliente`) REFERENCES `cliente` (`idCliente`) ON DELETE NO ACTION ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_venda_funcionario1` FOREIGN KEY (`fkFuncionario`) REFERENCES `funcionario` (`idFuncionario`) ON DELETE NO ACTION ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
