# Created by: Derek Musselmann aka phrac <derek@disflux.com>
# $FreeBSD$

PORTNAME=	venom
PORTVERSION=	20140302
CATEGORIES=	net-im
MASTER_SITES=	GH

MAINTAINER=	derek@disflux.com
COMMENT=	A graphical client for the Tox core written in Vala/GTK

LICENSE=	GPLv3

BUILD_DEPENDS=	${LOCALBASE}/bin/valac:${PORTSDIR}/lang/vala
LIB_DEPENDS=	libgee.so:${PORTSDIR}/devel/libgee \
    		libtoxcore.so:${PORTSDIR}/net-im/tox-core

INSTALLS_ICONS=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	naxuroqa
GH_PROJECT=	Venom
GH_COMMIT=	140155e
GH_TAGNAME=	${GH_COMMIT}

USES=		cmake
USE_GNOME=	gtk30

.include <bsd.port.mk>
